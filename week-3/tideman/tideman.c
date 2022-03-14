#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // Iterate over voters
    for (int i = 0; i < candidate_count; i++)
    {
        // If name valid, add rank & return true
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    // If name not valid, return false
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // Iterate through all ranks of candidates to get higher pref
    for (int i = 0; i < candidate_count; i++)
    {
        // Iterate through all ranks of candidates to get lower pref
        for (int j = i + 1; j < candidate_count; j++)
        {
            // Update preference for candidate rank[i] over rank[j]
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // Need idx of pair count
    pair_count = 0;
    // Iterate through all preferences for winner index
    for (int i = 0; i < candidate_count; i++)
    {
        // Iterate through all preferences for loser index
        for (int j = 0; j < candidate_count; j++)
        {
            // Check if pref has vote but no ties
            if (preferences[i][j] > 0 &&
                preferences[i][j] > preferences[j][i])
            {
                // Add each pref to pairs[], specifying winner & loser index
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                // Increment pair_count
                pair_count++;
            }
        }
    }

    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // Sort algorithm -- selection sort
    // Iterate over pair_count for base val
    for (int i = 0; i < pair_count; i++)
    {
        // vars to swap higher pair with [i] -- reset each cycle
        int high_idx = i;
        pair swap_pair;

        // Iterate over pair_count for check val
        for (int j = i + 1; j < pair_count; j++)
        {
            // Check if pref has higher count
            if (preferences[pairs[j].winner][pairs[j].loser] > preferences[pairs[high_idx].winner][pairs[high_idx].loser])
            {
                // If so, reassign highest idx/pair to swap with pairs[i]
                high_idx = j;
                swap_pair = pairs[j];
            }
        }

        // Don't reassign if not changing -- strength of victory doesn't matter
        if (high_idx != i)
        {
            // Assign pairs[i] in place of highest idx
            pairs[high_idx] = pairs[i];
            // Assign highest pair to pairs[i]
            pairs[i] = swap_pair;
        }
    }

    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // Linear search algorithm to find if, for each candidate, they are the
    // loser of an edge

    // // skip final:
    // pair_count = 7;
    // pairs[0].winner = 0; pairs[0].loser = 1;
    // pairs[1].winner = 1; pairs[1].loser = 4;
    // pairs[2].winner = 4; pairs[2].loser = 2;
    // pairs[3].winner = 4; pairs[3].loser = 3;
    // pairs[4].winner = 3; pairs[4].loser = 5;
    // pairs[5].winner = 5; pairs[5].loser = 1;
    // pairs[6].winner = 2; pairs[6].loser = 1;

    /*
    skip final:
    false true  false false false false
    false false false false true  false
    false false false false false false
    false false false false false true
    false false true  true  false false
    false false false false false false
    0 > 1
    1 > 4
    4 > 2
    4 > 3
    3 > 5
    NO 5 > 1
    NO 2 > 1
    */

    // // skip mid:
    // pair_count = 5;
    // pairs[0].winner = 2; pairs[0].loser = 0;
    // pairs[1].winner = 4; pairs[1].loser = 1;
    // pairs[2].winner = 1; pairs[2].loser = 3;
    // pairs[3].winner = 3; pairs[3].loser = 4;
    // pairs[4].winner = 4; pairs[4].loser = 2;

    /*
    skip mid:
    false false false false false
    false false false true  false
    true  false false false false
    false false false false false
    false true  true  false false
    2 > 0
    4 > 1
    1 > 3
    4 > 2
    NO 3 > 4
    */

    // iterate through pairs to lock
    for (int i = 0; i < pair_count; i++)
    {
        // printf("\nlocking edge %i...\n", i);

        // test if cycle for edge locking
        bool cycle = false;
        // store predecessors to edge
        int pred_cnt = 0;
        int preds[MAX * (MAX - 1) / 2];
        for (int j = 0; j < pair_count; j++)
        {
            // check if pred -- locked & loser is new winner
            if (locked[pairs[j].winner][pairs[j].loser] &&
                pairs[i].winner == pairs[j].loser)
            {
                preds[pred_cnt] = j;
                pred_cnt++;
            }
        }

        // if found, check each predecessor pair for cycle
        if (pred_cnt != 0)
        {
            // printf("%i preds found for edge %i!!!\n", pred_cnt, i);

            // cycle # of times preds found for edge
            for (int j = 0; j < pred_cnt; j++)
            {
                bool all_preds_checked = false;
                while (!all_preds_checked)
                {
                    // printf("all preds %s\n", all_preds_checked ? "checked" : "not checked");
                    // printf("checking pred edge %i for cycle with new edge %i...\n", preds[j], i);
                    // If pred locked & new loser is winner, cycle
                    if (locked[pairs[preds[j]].winner][pairs[preds[j]].loser] &&
                        pairs[preds[j]].winner == pairs[i].loser)
                    {
                        // printf("cycle found between pairs %i & %i!!!\n", preds[j], i);
                        cycle = true;
                        all_preds_checked = true;
                    }
                    // If not, check next pred edge for cycle
                    else
                    {
                        // printf("cycle not found between pairs %i & %i, checking for next pred...\n", preds[j], i);
                        // int remaining_preds = pair_count;
                        bool new_pred = false;
                        for (int k = 0; k < pair_count; k++)
                        {
                            // If pred, reassign & check for cycle
                            if (locked[pairs[k].winner][pairs[k].loser] &&
                                pairs[preds[j]].winner == pairs[k].loser)
                            {
                                // printf("new pred is edge %i!!!\n", k);
                                preds[j] = k;
                                new_pred = true;
                            }
                        }

                        // If no more preds, all checked
                        if (!new_pred)
                        {
                            // printf("no more preds found!!!\n");
                            all_preds_checked = true;
                        }
                    }
                }
            }
        }
        // else
        // {
            // printf("no pred found for pair %i!!!\n", i);
        // }

        if (!cycle)
        {
            // printf("no cycle found, pair %i locked\n", i);
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }

    return;
}

// Print the winner of the election
void print_winner(void)
{

    // // Test -- single winner, should be Alice only
    // pair_count = 6;
    // locked[0][0] = false;
    // locked[0][1] = locked[0][2] = locked[0][3] = true;
    // locked[1][0] = locked[1][1] = false;
    // locked[1][2] = locked[1][3] = true;
    // locked[2][0] = locked[2][1] = locked[2][2] = false;
    // locked[2][3] = true;
    // locked[3][0] = locked[3][1] = locked[3][2] = locked[3][3] = false;

    // // Test -- some ties, should be Charlie only
    // pair_count = 4;
    // for (int i = 0; i < 4; i++)
    //     for (int j = 0; j < 4; j++)
    //         locked[i][j] = false;
    // locked[2][0] = true;
    // locked[0][1] = true;
    // locked[0][3] = true;
    // locked[1][3] = true;

    // Datatype to store winner idxs, # of parents, & whether source
    typedef struct
    {
        int candidate;
        int parents;
    }
    winner;

    winner winners[pair_count];
    bool has_src = false;
    int lowest_prnt_cnt = pair_count, src_idx;

    // Iterate through all pairs to compare winners
    for (int i = 0; i < pair_count; i++)
    {
        // Iterate through all pairs to count parents
        winners[i].candidate = pairs[i].winner;
        winners[i].parents = 0;
        for (int j = 0; j < pair_count; j++)
        {
            if (locked[pairs[j].winner][pairs[j].loser] &&
                pairs[j].loser == winners[i].candidate)
            {
                winners[i].parents++;
            }
        }

        // If no parent edges, source
        if (winners[i].parents == 0)
        {
            has_src = true;
            src_idx = winners[i].candidate;
        }
        else
        {
            if (winners[i].parents < lowest_prnt_cnt)
            {
                lowest_prnt_cnt = winners[i].parents;
            }
        }
    }

    if (has_src)
    {
        printf("%s\n", candidates[src_idx]);
    }
    else
    {
        for (int i = 0; i < pair_count; i++)
        {
            if (winners[i].parents == lowest_prnt_cnt)
            {
                printf("%s\n", candidates[winners[i].candidate]);
            }
        }
    }

    return;
}
