#include <stdio.h>
#include <string.h>

void MostWatchedMovie(SeatingData s[][6], int rows) {
  int i, j, min;
  int totalOccupancy[rows];
  SeatingData MostWatched[rows];

  // Calculate total occupancy for each movie
  for (i = 0; i < rows; i++) {
    totalOccupancy[i] = 0;
    for (j = 0; j < 6; j++) {
      totalOccupancy[i] += s[i][j].Occupancy;
    }
    // Copy the first showtime's movie title to MostWatched
    strcpy(MostWatched[i].MovieTitle, s[i][0].MovieTitle);
    MostWatched[i].Occupancy = totalOccupancy[i];
  }

  // Selection Sort based on total occupancy
  for (i = 0; i < rows - 1; i++) {
    min = i;
    for (j = i + 1; j < rows; j++) {
      if (MostWatched[min].Occupancy < MostWatched[j].Occupancy) {
        min = j;
      }
    }
    // Swap the elements in the MostWatched array
    if (min != i) {
      SeatingData temp = MostWatched[i];
      MostWatched[i] = MostWatched[min];
      MostWatched[min] = temp;
    }
  }

  // Display the top 3 most-watched movies
  printf("Top 3 Most Watched Movies:\n");
  for (i = 0; i < 3 && i < rows; i++) {
    printf("%d. %s with %d seats\n", i + 1, MostWatched[i].MovieTitle, MostWatched[i].Occupancy);
  }
}

int main() {
  SeatingData s[3][6] = {
    {{"Movie A", 120}, {"Movie A", 130}, {"Movie A", 140}, {"Movie A", 150}, {"Movie A", 160}, {"Movie A", 170}},
    {{"Movie B", 150}, {"Movie B", 160}, {"Movie B", 170}, {"Movie B", 180}, {"Movie B", 190}, {"Movie B", 200}},
    {{"Movie C", 90}, {"Movie C", 100}, {"Movie C", 110}, {"Movie C", 120}, {"Movie C", 130}, {"Movie C", 140}}
  };

  MostWatchedMovie(s, 3);

  return 0;
}
