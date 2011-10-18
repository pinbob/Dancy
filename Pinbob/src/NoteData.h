#ifndef NOTEDATA_H
#define NOTEDATA_H

#include "NoteTypes.h"
#include "note_config.h"
#include <vector>
#include <string>
#include <map>
/* using std::string; */
/* #include "Attack.h" */

#define SHOW(x) (printf("%u %u %u %u\n", (x).left_, (x).down_, (x).up_, (x).right_))
#define BITFLAG(x) (*(int *)&(x) & 0x0000000f)

/*************************************************
 * Data of a row
 * That is states of all 4 arrows at a given time
 *************************************************/
struct ROW {
  unsigned left_ : 1;                   /* one bit */
  unsigned down_ : 1;
  unsigned up_   : 1;
  unsigned right_: 1;
  unsigned align_: 4;
};

/**********************************************/
/* Information of a song (with a particular   */
/* dificullty) which can be retrived from one */
/* BMS file                                   */
/**********************************************/
struct SongInfo {
  std::string title_;
  std::string genre_;
  std::string artist_;
  int         difficulty_;
};


/****************************************************************/
/* Hold the information of a bms file (with difficulty defined) */
/* and get loaded when this song/bms is chosen                  */
/****************************************************************/
class NoteData {
public:
  NoteData(): last_idx_(0), last_bpm_(0) {}
  ~NoteData() {}

  /* Setters and Getters */

  int   num_panels() const             { return num_panels_; }
  void  set_num_panels(int num_panels) { num_panels_ = num_panels; }; // TODO: make sure all tracks are of the same length

  double bpm()             { return bpm_; }
  void set_bpm(double bpm) { bpm_ = bpm; cur_bpm_ = bpm; }


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

  /**
   * All TapNotes are listed regardless of there duration
   * They are simply indexed using panel number and row number
   */
  void set_tap_note(int panel, int row, TapNote t);

  void insert_preset_bpm(int seq, double bpm) {
    preset_bpm_.insert(std::pair< int, double >(seq, bpm));
  }
  double preset_bpm(int seq) { return preset_bpm_[seq]; }

  void set_cur_bpm(double bpm) {
    cur_bpm_ = bpm;
    var_bpm_.push_back(bpm);
  }
  double cur_bpm() const { return cur_bpm_; }

  double bpm_now(int row) { return var_bpm_[row]; }
  /**
   * Query if there is a note at a given time
   * It is used by arrow controller
   * MODIFIES: last_idx_
   */
  ROW GetNoteAtTime(unsigned time);

  /* For purpose of Debugging */
  inline std::vector<TapNote> &get_panel(int panel) {
    return tap_notes_[panel];
  }

  int GetBPMNum() {return var_bpm_.size();}
  std::vector< double > &GetBPM() { return var_bpm_; }
  std::map< int, double > &GetPreset() {return preset_bpm_; }
  int GetRows() { return tap_notes_[4].size(); }
private:
  std::vector< TapNote >      tap_notes_[MAX_NOTE_PANELS];
  int                         num_panels_; /* 4 by default */
  double                      bpm_;        /* beat per minute */
  int                         last_idx_;   /* last index of the query of note */
  std::map< int, double >     preset_bpm_;
  std::vector< double >       var_bpm_;
  double                      cur_bpm_;
  double                      last_bpm_;
  void PadTapNotes(int rows);
};

#endif /* NOTEDATA_H */
