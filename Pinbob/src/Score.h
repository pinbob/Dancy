/*
 * Score.h
 *
 *  Created on: Jul 19, 2011
 *      Author: Zhang Wenli
 */

#ifndef SCORE_H_
#define SCORE_H_

#include <stack>
#include <irrlicht.h>

using namespace irr;

class Score{
public:
        Score();
        void clearScore();

        /*Call ...Hit() everytime user click an arrow */
        void perfectHit();
        void wellDownHit();
        void goodHit();
        void badHit();
        void missedHit();

        /* These five functions will call setCombo automatically.
         * The first three setCombo(true),
         * later two setCombo(false)
         */
        u32 getPerfectCount();
        u32 getWellDoneCount();
        u32 getGoodCount();
        u32 getBadCount();
        u32 getMissedCount();

        /* return current score, return 0 if smaller than 0 */
        u32 getScore();

        /* if the last in stack combo is 0, return false,
         * else, return true
         */
        bool isCombo();

private:
        unsigned int perfectCount;
        unsigned int wellDoneCount;
        unsigned int goodCount;
        unsigned int badCount;
        unsigned int missedCount;

        std::stack<unsigned int> combo;

        void setCombo(bool isCombo);
};



#endif /* SCORE_H_ */
