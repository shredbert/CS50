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
    // Selection sort algorithm -- iterate over pair_count for base val
    for (int i = 0; i < pair_count; i++)
    {
        // Vars to swap higher pair with [i] -- reset each cycle
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
    // Iterate through pairs to lock
    for (int i = 0; i < pair_count; i++)
    {
        // Test for edge cycle before locking
        bool cycle = false;

        // Store # of predecessors to edge
        int pred_cnt = 0;
        int preds[MAX * (MAX - 1) / 2];
        for (int j = 0; j < pair_count; j++)
        {
            // Pred == is locked & loser is new winner
            if (locked[pairs[j].winner][pairs[j].loser] &&
                pairs[i].winner == pairs[j].loser)
            {
                preds[pred_cnt] = j;
                pred_cnt++;
            }
        }

        // If preds found, check each predecessor pair for cycle
        if (pred_cnt != 0)
        {
            // Cycle # of times preds found for edge
            for (int j = 0; j < pred_cnt; j++)
            {
                bool all_preds_checked = false;
                while (!all_preds_checked)
                {
                    // If pred locked & new loser is winner, cycle
                    if (locked[pairs[preds[j]].winner][pairs[preds[j]].loser] &&
                        pairs[preds[j]].winner == pairs[i].loser)
                    {
                        cycle = true;
                        all_preds_checked = true;
                    }
                    // If not, check next pred edge for cycle
                    else
                    {
                        bool new_pred = false;

                        for (int k = 0; k < pair_count; k++)
                        {
                            // If pred, reassign & check for cycle
                            if (locked[pairs[k].winner][pairs[k].loser] &&
                                pairs[preds[j]].winner == pairs[k].loser)
                            {
                                preds[j] = k;
                                new_pred = true;
                            }
                        }

                        // If no more preds, all checked
                        if (!new_pred)
                        {
                            all_preds_checked = true;
                        }
                    }
                }
            }
        }

        // If cycle not found, can lock
        if (!cycle)
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }

    return;
}

// Print the winner of the election
void print_winner(void)
{
    // Iterate through candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // Count # of times i has not lost
        int non_losing_edges = 0;

        // Iterate through candidates again to increment times not lost
        for (int j = 0; j < candidate_count; j++)
        {
            // Check if i has been loser in edge
            if (!locked[j][i])
            {
                non_losing_edges++;

                // If # of non-losing edges == # of candidates, print name --
                // never been won against more than any other candidate
                if (non_losing_edges == candidate_count)
                {
                    printf("%s\n", candidates[i]);
                }
            }
        }
    }
    return;
}
