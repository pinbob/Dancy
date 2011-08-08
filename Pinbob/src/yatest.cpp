#include <stdio.h>
#include <cstdlib>
#include <ctime>
#include <string>
#include <sys/time.h>
#include <signal.h>
#include <vector>
#include "NotesLoader.h"
#include "NoteData.h"
#include "Song.h"
#include "SongCollection.h"

#include "../include/irrKlang.h"
#include "../include/conio.h"
using namespace std;
using namespace irrklang;

#define TICK(x) ((x) ? '#' : ' ')


SongCollection collection;              // Save the collection of all songs
int count;                              // [DEBUG] number of queries
NoteData *note_data;                    // pointer to notedata series
ISoundEngine *engine;                   // sound engine
time_t begin;                           // [DEBUG]
struct timeval tstart;                  // [DEBUG]

void msg(int num) {
  count++;
  if (count >= 5000) {
    return;
  }
  static struct ROW row;
  struct timeval t;
  gettimeofday(&t, NULL);
  row = note_data->GetNoteAtTime((t.tv_sec - tstart.tv_sec) * 1000 + (t.tv_usec - tstart.tv_usec)/1000 );
  if (BITFLAG(row)) {
    SHOW(row);
    printf("%4c%4c%4c%4c\n",
           TICK(row.left_),
           TICK(row.down_),
           TICK(row.up_),
           TICK(row.right_));
  }
}

int main() {
  count = 0;

  // Step 1: Load a song directory
  collection.LoadSongs("../asset/songs");
  if (collection.song_list().size() != 5) {
    printf("pity\n");
  } else {
    printf("aaa\n");
  }

  // Step 2: Get the NoteData series for [1] song [2] difficulty
  note_data = &collection.GetNote(0, 0);
  printf("Title: %s\n", collection.GetSong(0).main_title().c_str());
  
  struct itimerval tick;
  tick.it_value.tv_sec = 1;
  tick.it_value.tv_usec = 0;
  tick.it_interval.tv_sec = 0;
  tick.it_interval.tv_usec = 10000;

  signal(SIGALRM, msg);
  setitimer(ITIMER_REAL, &tick, NULL);
  gettimeofday(&tstart, NULL);

  // engine = createIrrKlangDevice();
  // if (!engine) {
  //   printf("Could not startup the engine\n");
  //   return 0;
  // }

  // engine->play2D("./01.ogg");

  while (1) {
    sleep(1);
    if (count >= 5200) {
      // engine->drop();
      break;
    }
  }
  vector<TapNote> v = note_data->get_panel(3);
  for (int i = 0; i < 600; i++) {
    if (*(char *)&v[i] != 0)
      printf("%d\n", *(char *)&v[i]);
  }
  return 0;
}
