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
bool been_here[MAX];

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool is_circle(int i, int search);

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
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (i < j)
            {
                preferences[ranks[i]][ranks[j]]++;
            }
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    int c = 0;
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[c].winner = i;
                pairs[c].loser = j;
                c++;
            }
        }
    }
    pair_count = c;
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    pair temp;
    int swap_counter = -1;

    while (swap_counter)
    {
        swap_counter = 0;
        for (int i = 0; i < pair_count - 1; i++)
        {
            if (preferences[pairs[i].winner][pairs[i].loser] < preferences[pairs[i + 1].winner][pairs[i + 1].loser])
            {
                temp = pairs[i];
                pairs[i] = pairs[i + 1];
                pairs[i + 1] = temp;
                swap_counter++;
            }
        }
    }

    for (int i = 0; i < pair_count; i++)
    {
        printf("Pair %i: \n Winner: %s \n Loser: %s \n margin: %i \n\n", i, candidates[pairs[i].winner], candidates[pairs[i].loser],
               preferences[pairs[i].winner][pairs[i].loser]);
    }


    return;
}

//found this function on github through reddit. Thanks guys.
bool is_circle(int i, int search)
{
    if (been_here[i])
    {
        return false;
    }
    been_here[i] = true;

    if (locked[i][search])
    {
        return true;
    }
    for (int j = 0; j < candidate_count; j++)
    {
        if (locked[i][j])
        {
            if (is_circle(j, search))
            {
                return true;
            }
        }
    }

    return false;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    //okay so the first one has to be locked in right
    locked[pairs[0].winner][pairs[0].loser] = true;
    
    int top = pairs[0].winner;
    
    for (int i = 1; i < pair_count; i++)
    {
        //and if the next ones put in aren't leading to the top then they are safe
        if (pairs[i].loser != top)
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
        else
        {
            if (!is_circle(top, pairs[i].winner))
            {
                locked[pairs[i].winner][pairs[i].loser] = true;
                top = pairs[i].winner;
            }
        }
        
        for (int j = 0; j < candidate_count; j++)
        {
            been_here[j] = false;
        }
        
    }
    //just for debugging. Prints out the chart so yeah
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            printf("%i  ", locked[i][j]);
        }
        printf("\n");
    }

    return;
}

// Print the winner of the election
void print_winner(void)
{
    // so we gotta find a candidate that has no other candidates locked in above it.
    for (int i = 0; i < candidate_count; i++)
    {
        int count = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            if (!locked[j][i])
            {
                count++;
            }
        }
        if (count == candidate_count)
        {
            printf("%s\n", candidates[i]);
        }
    }
    return;
}
