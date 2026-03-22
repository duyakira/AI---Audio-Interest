#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_SONGS 1000
#define MAX_LINE 256

// Struct lưu thông tin bài hát
typedef struct {
    char title[100];
    char artist[100];
    char genre[50];
    char mood[50];
} Song;

// Load dữ liệu từ CSV
int loadSongs(const char *filename, Song songs[]) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Cannot open file!\n");
        return 0;
    }

    char line[MAX_LINE];
    int count = 0;

    // Bỏ qua header
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%99[^,],%99[^,],%49[^,],%49[^\n]",
               songs[count].title,
               songs[count].artist,
               songs[count].genre,
               songs[count].mood);
        count++;
    }

    fclose(file);
    return count;
}

// Lọc bài hát theo mood
int filterSongs(Song songs[], int total, Song filtered[], const char *mood) {
    int count = 0;
    for (int i = 0; i < total; i++) {
        if (strcmp(songs[i].mood, mood) == 0) {
            filtered[count++] = songs[i];
        }
    }
    return count;
}

// Shuffle mảng
void shuffle(Song arr[], int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Song temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

// In playlist
void printPlaylist(Song songs[], int n) {
    printf("\n🎵 Your Playlist:\n");
    for (int i = 0; i < n; i++) {
        printf("%d. %s - %s (%s)\n",
               i + 1,
               songs[i].title,
               songs[i].artist,
               songs[i].genre);
    }
}

int main() {
    Song songs[MAX_SONGS];
    Song filtered[MAX_SONGS];

    int totalSongs = loadSongs("C:\\Users\\Admin\\Documents\\C-C++\\project\\songs.csv", songs);

    if (totalSongs == 0) return 1;

    char mood[50];
    printf("Enter your mood (happy/sad/energetic/...): ");
    scanf("%49s", mood);

    int filteredCount = filterSongs(songs, totalSongs, filtered, mood);

    if (filteredCount == 0) {
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