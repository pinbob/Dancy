#include <stdio.h>
#include "NotesLoader.h"
#include "NoteData.h"
#include <cstdlib>
#include <ctime>
#include <sys/time.h>
#include <signal.h>
#include <vector>

#include "./include/irrKlang.h"
#include "./include/conio.h"
using namespace std;
using namespace irrklang;

#define TICK(x) ((x) ? '#' : ' ')

NotesLoader nl;
int count;
NoteData note_data;
ISoundEngine *engine;
time_t begin;
struct timeval tstart;

void msg(int num) {
  count++;
  if (count >= 500) {
    return;
  }
  static struct ROW row;
  struct timeval t;
  gettimeofday(&t, NULL);
  row = note_data.GetNoteAtTime((t.tv_sec - tstart.tv_sec) * 1000 + (t.tv_usec - tstart.tv_usec)/1000 );
  if (BITFLAG(row))
    printf("%4c%4c%4c%4c\n",
           TICK(row.left_),
           TICK(row.down_),
           TICK(row.up_),
           TICK(row.right_));
}

int main() {
  count = 0;
  nl.LoadFromFile(NULL, &note_data);
  struct itimerval tick;
  tick.it_value.tv_sec = 1;
  tick.it_value.tv_usec = 0;
  tick.it_interval.tv_sec = 0;
  tick.it_interval.tv_usec = 10000;

  signal(SIGALRM, msg);
  setitimer(ITIMER_REAL, &tick, NULL);
  gettimeofday(&tstart, NULL);

  engine = createIrrKlangDevice();
  if (!engine) {
    printf("Could not startup the engine\n");
    return 0;
  }

  engine->play2D("./getout.ogg");

  while (1) {
    sleep(1);
    if (count >= 520) {
      engine->drop();
      break;
    }
  }
  vector<TapNote> v = note_data.get_panel(3);
  for (int i = 0; i < 600; i++) {
    if (*(char *)&v[i] != 0)
      printf("%d\n", *(char *)&v[i]);
  }
  return 0;
}
