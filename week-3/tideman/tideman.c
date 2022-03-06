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
            // printf("rank %i: candidate %i\n", rank, i);
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
        // printf("%i (i) wins over: ", ranks[i]);
        // Iterate through all ranks of candidates to get lower pref
        // NOTE: Why no segmentation fault? can't j be out of bounds here?
        for (int j = i + 1; j < candidate_count; j++)
        {
            // printf("%i (j) loses,", ranks[j]);
            // Update preference for candidate rank[i] over rank[j]
            preferences[ranks[i]][ranks[j]]++;
            // printf("pref %i > %i count: %i\n", ranks[i], ranks[j], preferences[ranks[i]][ranks[j]]);
        }
        // printf("\n");
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO: Init pair_count so can increment
    pair_count = 0;
    // TODO: Iterate through all preferences to get upper pref
    for (int i = 0; i < candidate_count; i++)
    {
        // TODO: Iterate through all preferences to get lower pref
        for (int j = 0; j < candidate_count; j++)
        {
            // TODO: Check if pref is > 0
            if (preferences[i][j] > 0)
            {
                // TODO: Add each pref to pairs[], specifying winner & loser
                // index???
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                // TODO: Increment pair_count
                // printf("pair %i: winner = %i, loser = %i\n", pair_count, i, j);
                pair_count++;
            }
        }
    }
    // printf("\n");
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // testins
    // printf("Prefs list:\n");
    // for (int i = 0; i < pair_count; i++)
    // {
    //     printf("%i ", preferences[pairs[i].winner][pairs[i].loser]);
    // }
    // printf("\n");

    // Selection sort
    // Iterate over pair_count for base val
    for (int i = 0; i < pair_count; i++)
    {
        // vars to swap higher pair with [i] -- reset each cycle
        int high_idx = i;
        pair swap_pair;
        // printf("comparing %i...\n", preferences[pairs[i].winner][pairs[i].loser]);

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

        // Don't reassign if not changing
        // NOTE: Slightly more efficient? Or unnecessary?
        if (high_idx != i)
        {
            // printf("index %i is highest!\n", high_idx);
            // Assign pairs[i] in place of highest idx
            pairs[high_idx] = pairs[i];
            // Assign highest pair to pairs[i]
            pairs[i] = swap_pair;
        }
    }

    // testins
    // printf("\nnew prefs list:\n");
    // for (int i = 0; i < pair_count; i++)
    // {
    //     printf("preference: %i\n", preferences[pairs[i].winner][pairs[i].loser]);
    // }
    // printf("\n");
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        printf("%s over %s: %i\n", candidates[pairs[i].winner], candidates[pairs[i].loser], preferences[pairs[i].winner][pairs[i].loser]);
        printf("locked: %i\n", locked[pairs[i].winner][pairs[i].loser]);
    }
    printf("\n");

    // Iterate over sorted pairs
    for (int i = 0; i < pair_count; i++)
    {
        // If inverse of pair isn't already locked, lock
        if (!locked[pairs[i].loser][pairs[i].winner])
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }

    // testins
    for (int i = 0; i < pair_count; i++)
    {
        printf("%s over %s: %i\n", candidates[pairs[i].winner], candidates[pairs[i].loser], preferences[pairs[i].winner][pairs[i].loser]);
        printf("locked: %i\n", locked[pairs[i].winner][pairs[i].loser]);
    }
    printf("\n");
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // Take winning pair & print name if locked
    for (int i = 0; i < pair_count; i++)
    {
        if (locked[pairs[i].winner][pairs[i].loser])
        {
            printf("%s\n", candidates[pairs[i].winner]);
            break;
        }
    }
    return;
}
