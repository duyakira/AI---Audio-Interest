#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <time.h>

#define MAX_SONGS 1000
#define MAX_LINE 256

// Updated Struct: Perfectly aligned with the Valence-Arousal theory
typedef struct
{
    char title[150];
    char album[150];
    char artist[100];
    float energy;  // Replaced popularity/danceability/acousticness
    float valence; // Added valence
    char mood[50];
} Song;

// Upgraded parser to extract Energy and Valence
int loadSongs(const char *filename, Song songs[])
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        printf("Cannot open file! Make sure '%s' is in the same folder.\n", filename);
        return 0;
    }

    char line[1024];
    int count = 0;

    // Skip the header row
    fgets(line, sizeof(line), file);

    // Read each line
    while (fgets(line, sizeof(line), file) && count < MAX_SONGS)
    {
        char *token = strtok(line, ",");

        if (token != NULL)
        {
            // 1. Name (Title)
            strncpy(songs[count].title, token, sizeof(songs[count].title) - 1);

            // 2. Album
            token = strtok(NULL, ",");
            if (token)
                strncpy(songs[count].album, token, sizeof(songs[count].album) - 1);

            // 3. Artist
            token = strtok(NULL, ",");
            if (token)
                strncpy(songs[count].artist, token, sizeof(songs[count].artist) - 1);

            // Skip 4 through 9 (ID, Release Date, Popularity, Length, Danceability, Acousticness)
            for (int i = 0; i < 6; i++)
            {
                strtok(NULL, ",");
            }

            // 10. Energy (The "Arousal" metric)
            token = strtok(NULL, ",");
            if (token)
                songs[count].energy = atof(token);

            // Skip 11 and 12 (Instrumentalness, Liveness)
            strtok(NULL, ",");
            strtok(NULL, ",");

            // 13. Valence (The "Pleasure" metric)
            token = strtok(NULL, ",");
            if (token)
                songs[count].valence = atof(token);

            // Skip 14 through 18 (Loudness, Speechiness, Tempo, Key, Time Signature)
            for (int i = 0; i < 5; i++)
            {
                strtok(NULL, ",");
            }

            // 19. Mood (The final column)
            token = strtok(NULL, ",\n\r");
            if (token)
            {
                strncpy(songs[count].mood, token, sizeof(songs[count].mood) - 1);
                // Clean up trailing whitespace/newlines
                songs[count].mood[strcspn(songs[count].mood, "\r\n")] = 0;
            }

            count++;
        }
    }

    fclose(file);
    return count;
}

// Filter songs by mood
int filterSongs(Song songs[], int total, Song filtered[], const char *mood)
{
    int count = 0;
    for (int i = 0; i < total; i++)
    {
        if (strcasecmp(songs[i].mood, mood) == 0)
        {
            filtered[count++] = songs[i];
        }
    }
    return count;
}

// Fisher-Yates Shuffle
void shuffle(Song arr[], int n)
{
    for (int i = n - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        Song temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

// Updated Display output to prove the system logic and match the report terminology
void printPlaylist(Song songs[], int n)
{
    printf("\nYour AuraBeat Playlist:\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d. %s - %s\n", i + 1, songs[i].title, songs[i].artist);
        // Changed "Energy" to "Arousal" to perfectly match the V-A theoretical model
        printf("   [Album: %s | Valence: %.2f | Arousal: %.2f]\n",
               songs[i].album, songs[i].valence, songs[i].energy);
        printf("----------------------------------------------------\n");
    }
    printf("\n");
}

int main()
{
    Song songs[MAX_SONGS];
    Song filtered[MAX_SONGS];

    int totalSongs = loadSongs("data_moods.csv", songs);

    if (totalSongs == 0)
        return 1;

    int choice;
    char targetMood[50];

    // 1. Print the interactive menu
    printf("\nHow are you feeling today?\n");
    printf("1. Happy\n");
    printf("2. Sad\n");
    printf("3. Energetic\n");
    printf("4. Calm\n");
    printf("Enter the number of your mood (1-4): ");

    // 2. Grab the integer
    scanf("%d", &choice);

    // 3. Translate the integer into the correct string
    switch (choice)
    {
    case 1:
        strcpy(targetMood, "Happy");
        break;
    case 2:
        strcpy(targetMood, "Sad");
        break;
    case 3:
        strcpy(targetMood, "Energetic");
        break;
    case 4:
        strcpy(targetMood, "Calm");
        break;
    default:
        printf("Invalid choice! Please run the program again and select 1-4.\n");
        return 1;
    }

    // 4. Pass the newly translated targetMood string into the filter
    int filteredCount = filterSongs(songs, totalSongs, filtered, targetMood);

    if (filteredCount == 0)
    {
        printf("No songs found for this mood!\n");
        return 0;
    }

    // Random seed
    srand(time(NULL));

    // Shuffle
    shuffle(filtered, filteredCount);

    int playlistSize = filteredCount < 5 ? filteredCount : 5;

    printPlaylist(filtered, playlistSize);

    return 0;
}