#ifndef TICTACTOE3D_PLAYER_HPP
#define TICTACTOE3D_PLAYER_HPP

#include "constants.hpp"
#include "deadline.hpp"
#include "move.hpp"
#include "gamestate.hpp"
#include <vector>

namespace TICTACTOE3D
{

class Player
{
public:
    ///perform a move
    ///\param pState the current state of the board
    ///\param pDue time before which we must have returned
    ///\return the next state the board is in after our move
    GameState play(const GameState &pState, const Deadline &pDue);

private:
    int minimax(GameState const &state, int const& player, int depth);
    static int eval(GameState const &state);
    int alphabeta(const GameState &state, int player, int depth, int alpha, int beta);
    static bool order_by_value(const GameState &g1, const GameState &g2);

};

/*namespace TICTACTOE3D*/ }

#endif