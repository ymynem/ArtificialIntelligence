#include "player.hpp"
#include <cstdlib>
#include <limits.h>
#include <algorithm>

using namespace TICTACTOE3D;


namespace TICTACTOE3D
{

GameState Player::play(const GameState &pState,const Deadline &pDue)
{
    std::vector<GameState> lNextStates;
    pState.findPossibleMoves(lNextStates);

    if (lNextStates.size() == 0) return GameState(pState, Move());

    /*
     * Here you should write your clever algorithms to get the best next move, ie the best
     * next state. This skeleton returns a random move instead.
     */
    int max = INT_MIN;
    GameState bestState;
    int depth = 1;
    
    for (int i = 0; i < lNextStates.size(); ++i) {
        int value = alphabeta(lNextStates[i], pState.getNextPlayer(), depth, INT_MIN, INT_MAX);	//lNextStates[i] 
        if (value > max) {
            max = value;
            bestState = lNextStates[i];
        }
        if (abs(pDue - TICTACTOE3D::Deadline::now()) < 1) {
            return bestState;
        }
    }

    return bestState;
}

bool Player::order_by_value(const GameState &g1, const GameState &g2) {
    return eval(g1) > eval(g2);
}

int Player::alphabeta(const GameState &state, int player, int depth, int alpha, int beta) {
	if(state.getMove().isEOG()) {   
        return eval(state);
    }
    if(depth == 5 ) {   
        return eval(state);
    }
    
    int v;
    if (player == CELL_X) {
    	std::vector<GameState> possibleStates;
    	state.findPossibleMoves(possibleStates);
   
    	if(depth == 5 || state.getMove().isEOG()) {   
        return eval(state);
    	}
        v = INT_MIN;
        std::sort(possibleStates.begin(), possibleStates.end(), order_by_value);
        for (int i = 0; i < possibleStates.size(); ++i) {
            v = std::max(v, alphabeta(possibleStates[i], state.getNextPlayer(), depth+1, alpha, beta));
            alpha = std::max(v, alpha);
            if (beta <= alpha) {
                break;
            }
        }
    } else {
    	if(depth == 5 || state.getMove().isEOG()) {   
        return eval(state);
    	}
    	std::vector<GameState> possibleStates;
    	state.findPossibleMoves(possibleStates);
    	
        v = INT_MAX;
        std::sort(possibleStates.rbegin(), possibleStates.rend(), order_by_value);
        for (int i = 0; i < possibleStates.size(); ++i) {
            v = std::min(v, alphabeta(possibleStates[i], state.getNextPlayer(), depth+1, alpha, beta));
            beta = std::min(v, beta);
            if (beta <= alpha) {
                break;
            }
        }
    }
    return v;
}

int Player::eval(const GameState &state) {
    
    if (state.getMove().isOWin()) {
        return INT_MIN;
    } else if (state.getMove().isXWin()) {
        return INT_MAX;
    }
    if (state.getMove().isEOG()) {
        return 0;
    }
 
    int value = 100;
    
     for (int i = 1, j = 1, k = 0; i < 4; ++i, ++j, ++k) {
        if (state.at(i,j,k) == CELL_X) {
            value += 100;
        } else if (state.at(i,j,k) == CELL_O) {
            value -= 10;
        }

        if (state.at(i,j,3-k) == CELL_X) {
            value += 100;
        } else if (state.at(i,j,3-k) == CELL_O) {
            value -= 10;
        }

        if (state.at(i,3-j,k) == CELL_X) {
            value += 100;
        } else if (state.at(i,3-j,k) == CELL_O) {
            value -= 10;
        }

        if (state.at(i,3-j,3-k) == CELL_X) {
            value += 100;
        } else if (state.at(i,3-j,3-k) == CELL_O) {
            value -= 10;
        }
    }
    for (int i = 0, j = 0, k = 0; i < 4; ++i, ++j, ++k) {
        if (state.at(i,j,k) == CELL_X) {
            value += 100;
        } else if (state.at(3-i,j,k) == CELL_O) {
            value -= 10;
        }

    }

    return value;

}

/*namespace TICTACTOE3D*/ }