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
  if (last_bpm_ == 0) {
    last_bpm_ = bpm_;
  }
  int cur_idx = last_idx_;
  int cur_bpm = last_bpm_;
  float interval;
  static double accum = 0;
  while (accum <= time) {
    cur_bpm = var_bpm_[cur_idx]?var_bpm_[cur_idx]:last_bpm_;
    last_bpm_ = cur_bpm;
    interval = 600000.0 / cur_bpm / 48;
    accum += interval;
    cur_idx++;
  }
  last_idx_ = cur_idx + 1;
  // printf("%d\n", last_idx_);
  /* interval between two row */
  // printf("last bpm: %.2f\n", var_bpm_[last_idx_]);

  // float interval = 60000.0 / var_bpm_[last_idx_] / 48;

  // printf("%f", var_bpm_[last_idx_]);
  // printf("%d\n", last_idx_);
  /* the direct index generated from time,
   * which may be inaccurate and hit on no target
   */
  // int idx = floor(time / interval);
  if (cur_idx >= (int)tap_notes_[0].size())
    return ROW{0, 0, 0, 0, 0};

  struct ROW row = { *(char *)(&tap_notes_[0][cur_idx])?1:0,
                     *(char *)(&tap_notes_[1][cur_idx])?1:0,
                     *(char *)(&tap_notes_[2][cur_idx])?1:0,
                     *(char *)(&tap_notes_[3][cur_idx])?1:0,
                     0 };
  return row;
  // whether there is a note in this row
  // if (BITFLAG(row))
  //   SHOW(row);

  /* if first trial failed, then search from the most recent note */
  // if (!BITFLAG(row)) {
  //   int i = last_idx_ - 1;
  //   while (++i < idx) {
  //     row = { *(char *)(&tap_notes_[0][i])?1:0,
  //             *(char *)(&tap_notes_[1][i])?1:0,
  //             *(char *)(&tap_notes_[2][i])?1:0,
  //             *(char *)(&tap_notes_[3][i])?1:0,
  //             0 };
  //     if (BITFLAG(row)) {
  //       last_idx_ = i + 1;
  //       last_bpm_ = var_bpm_[last_idx_];
  //       return row;
  //     } else {
  //       continue;
  //     }
  //   }
  //   if (i == idx) {
  //     last_idx_ = idx + 1;
  //     return ROW{0, 0, 0, 0, 0};
  //   }
  //   return ROW{0, 0, 0, 0, 0};
  // } else {
  //   last_idx_ = idx + 1;
  //   // printf("%x\n", *(char *)(&row));
  //   last_bpm_ = var_bpm_[last_idx_];
  //   return row;
  // }
}
