#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    int x = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            preferences[voter][rank] = i;
        }
        else
        {
            x += 1;
        }
    }
    if (x == candidate_count)
    {
        return false;
    }
    else
    {
        return true;
    }
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    int y = 0;
    for (int voter = 0; voter < voter_count; voter++)
    {
        for (int rank = 0; rank < candidate_count; rank++)
        {
            int x = 0;
            int z = 0;
            for (int i = 0; i < candidate_count; i++)
            {
                if (candidates[i].eliminated == true)
                {
                    x++;
                }
                else if (preferences[voter][rank] == i)
                {
                    candidates[i].votes = candidates[i].votes + 1;
                    z = i;
                    break;
                }
                else
                {
                    x++;
                }
            }
            if (x == z)
            {
                break;
            }
            else
            {
                y++;
            }
        }
    }
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    int x = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > floor(voter_count / 2))
        {
            printf("%s\n", candidates[i].name);
        }
        else
        {
            x++;
        }
    }
    if (x == candidate_count)
    {
        return false;
    }
    else
    {
        return true;
    }
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int x = 0;
    int y = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[candidate_count - (i + 1)].eliminated == false)
        {
            y = candidates[candidate_count - (i + 1)].votes;
            break;
        }
        else
        {
            x++;
        }
    }
    return y;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    int x = 0;
    int y = 0;
    int z = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == true)
        {
            z++;
        }
        else if (candidates[i].votes == min)
        {
            x++;
        }
        else
        {
            y++;
        }
    }
    if ((candidate_count - z) == x)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }
}