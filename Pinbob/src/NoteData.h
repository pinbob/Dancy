#ifndef NOTEDATA_H
#define NOTEDATA_H

#include "./NoteTypes.h"
#include "./note_config.h"
#include <map>
#include <vector>
/* #include "Attack.h" */

#define SHOW(x) (printf("%u %u %u %u\n", (x).left_, (x).down_, (x).up_, (x).right_))
#define BITFLAG(x) (*(int *)&(x) & 0x0000000f)

struct ROW {
  unsigned left_ : 1;
  unsigned down_ : 1;
  unsigned up_   : 1;
  unsigned right_: 1;
  unsigned align_: 4;
};


class NoteData {
public:
  NoteData(): last_idx_(0) {}
  ~NoteData() {}

  /* Setters and Getters */
  
  int   num_panels() const { return num_panels_; }
  void  set_num_panels(int num_panels) { num_panels_ = num_panels; }; // TODO: make sure all tracks are of the same length
  
  /* const map< unsigned int, Attack > */
  /*       &attack_map() const { return attack_map_; } */

  /* /\*************************************\/ */
  /* /\* Used to get a non-const reference *\/ */
  /* /\* for the use of initialization     *\/ */
  /* /\*************************************\/ */
  /* map< unsigned int, Attack > */
  /*       &attack_map() const { return attack_map_; } */

  /*************************************************/
  /* TapNote getter with-boundary-checking version */
  /* SAFE but SLOW                                 */
  /*************************************************/
  inline TapNote tap_note(unsigned int panel, int row) const {
    if (row < 0 || row >= (int) tap_notes_[panel].size())
      return TAP_EMPTY;
    return tap_notes_[panel][row];
  }

  /************************************************/
  /* TapNote getter non-boundary-checking version */
  /* DANGEROUS but FAST                           */
  /* BE SURE THAT 0 <= row <= num_rows            */
  /************************************************/
  inline TapNote tap_note_x(unsigned int panel, int row) const {
    return tap_notes_[panel][row];
  }

  /*************************************************************/
  /* All TapNotes are listed regardless of there duration      */
  /* They are simply indexed using panel number and row number */
  /*************************************************************/
  void set_tap_note(int panel, int row, TapNote t);

/* #ifdef DEBUG__ */
  inline std::vector<TapNote> &get_panel(int panel) {
    return tap_notes_[panel];
  }
/* #endif /\* DEBUG__ *\/ */

  int bpm() { return bpm_; }
  void set_bpm(int bpm) { bpm_ = bpm; }

  ROW GetNoteAtTime(unsigned time);
private:
  std::vector<TapNote>        tap_notes_[MAX_NOTE_PANELS];

  int                         num_panels_;
  int                         bpm_;
  int                         last_idx_;

  /* map< unsigned int, Attack > attack_map_; */

  void PadTapNotes(int rows);
  /* vector<HoldNote>            hold_notes_; */
};

#endif /* NOTEDATA_H */
