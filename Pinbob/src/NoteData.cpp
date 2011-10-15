#include <vector>
#include <math.h>
#include <stdio.h>
using std::vector;

#include "NoteData.h"

void NoteData::PadTapNotes(int rows) {
  int rows_needed_more = rows - tap_notes_[0].size() + 1;
  if (rows_needed_more < 0)
    return;
  rows_needed_more += 100; // optimization: give it a little more than needed

  for (int panel = 0; panel < num_panels_; panel++)
    tap_notes_[panel].insert(tap_notes_[panel].end(), rows_needed_more, TAP_EMPTY);
}

void NoteData::set_tap_note(int panel, int row, TapNote t) {
  if (row < 0)
    return;
  // ASSERT(panel < MAX_NOTE_PANELS);

  PadTapNotes(row);
  tap_notes_[panel][row] = t;
  var_bpm_.push_back(cur_bpm_);
}

ROW NoteData::GetNoteAtTime(unsigned time) {
  /* interval between two row */
  // printf("last bpm: %.2f\n", var_bpm_[last_idx_]);
  float interval = 60000.0 / var_bpm_[last_idx_] / 48;

  /* the direct index generated from time,
   * which may be inaccurate and hit on no target
   */
  int idx = floor(time / interval);
  if (idx > (int)tap_notes_[0].size())
    return ROW{0, 0, 0, 0, 0};

  struct ROW row = { *(char *)(&tap_notes_[0][idx])?1:0,
                     *(char *)(&tap_notes_[1][idx])?1:0,
                     *(char *)(&tap_notes_[2][idx])?1:0,
                     *(char *)(&tap_notes_[3][idx])?1:0,
                     0 };

  // whether there is a note in this row
  // if (BITFLAG(row))
  //   SHOW(row);

  /* if first trial failed, then search from the most recent note */
  if (!BITFLAG(row)) {
    int i = last_idx_ - 1;
    while (++i < idx) {
      row = { *(char *)(&tap_notes_[0][i])?1:0,
              *(char *)(&tap_notes_[1][i])?1:0,
              *(char *)(&tap_notes_[2][i])?1:0,
              *(char *)(&tap_notes_[3][i])?1:0,
              0 };
      if (BITFLAG(row)) {
        last_idx_ = i + 1;
        return row;
      } else {
        continue;
      }
    }
    if (i == idx - 1) {
      last_idx_ = idx + 1;
      return ROW{0, 0, 0, 0, 0};
    }
    return ROW{0, 0, 0, 0, 0};
  } else {
    last_idx_ = idx + 1;
    // printf("%x\n", *(char *)(&row));
    return row;
  }
}
