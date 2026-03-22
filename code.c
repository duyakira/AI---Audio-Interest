#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <time.h>

#define MAX_SONGS 1000
#define MAX_LINE 256

// Struct lưu thông tin bài hát
// Updated Struct to match Kaggle Dataset
typedef struct
{
    char title[150];    // 'name' column
    char album[150];    // 'album' column
    char artist[100];   // 'artist' column
    int popularity;     // 'popularity' column (0-100)
    float danceability; // 'danceability' column (0.0 to 1.0)
    float acousticness; // 'acousticness' column (0.0 to 1.0)
    char mood[50];      // We will assume the last column is 'mood'
} Song;

// Upgraded parser for the Kaggle Dataset
// Upgraded parser for the Kaggle Dataset
int loadSongs(const char *filename, Song songs[])
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        printf("Cannot open file! Make sure '%s' is in the same folder.\n", filename);
        return 0;
    }

    char line[1024]; // Increased line size for the massive 19-column Kaggle rows
    int count = 0;

    // Skip the header row
    fgets(line, sizeof(line), file);

    // Read each line
    while (fgets(line, sizeof(line), file) && count < MAX_SONGS)
    {
        // We use strtok to split the string at every comma
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

            // Skip 4 (ID) and 5 (Release Date)
            strtok(NULL, ",");
            strtok(NULL, ",");

            // 6. Popularity
            token = strtok(NULL, ",");
            if (token)
                songs[count].popularity = atoi(token);

            // Skip 7 (Length)
            strtok(NULL, ",");

            // 8. Danceability
            token = strtok(NULL, ",");
            if (token)
                songs[count].danceability = atof(token);

            // 9. Acousticness
            token = strtok(NULL, ",");
            if (token)
                songs[count].acousticness = atof(token);

            // Skip 10 through 18
            for (int i = 0; i < 9; i++)
            {
                strtok(NULL, ",");
            }

            // 19. Mood (The final column)
            token = strtok(NULL, ",\n\r"); // Look for comma OR newline at the end
            if (token)
            {
                strncpy(songs[count].mood, token, sizeof(songs[count].mood) - 1);

                // Optional: Clean up trailing whitespace/newlines from the mood string
                songs[count].mood[strcspn(songs[count].mood, "\r\n")] = 0;
            }

            count++;
        }
    }

    fclose(file);
    return count;
}

// Lọc bài hát theo mood
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

// Shuffle mảng
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

// In playlist
void printPlaylist(Song songs[], int n)
{
    printf("\n🎵 Your AuraBeat Playlist:\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d. %s - %s\n", i + 1, songs[i].title, songs[i].artist);
        printf("   [Album: %s | Pop: %d | Dance: %.2f]\n",
               songs[i].album, songs[i].popularity, songs[i].danceability);
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

    // char mood[50];
    // printf("Enter your mood (happy/sad/energetic/...): ");
    // scanf("%49s", mood);

    // int filteredCount = filterSongs(songs, totalSongs, filtered, mood);

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
        return 1; // Exit the program if they type something crazy like 99
    }

    // 4. Pass the newly translated targetMood string into your existing filter
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