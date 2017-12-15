import java.util.*;

public class TicTacToe {
 /**
  * Performs a move
  *
  * @param gameState
  * the current state of the board
  * @param deadline
  * time before which we must have returned
  * @return the next state the board is in after our move
  */
 public GameState play(final GameState gameState, final Deadline deadline) {
  Vector<GameState> nextStates = new Vector<GameState>();
  gameState.findPossibleMoves(nextStates);

  if (nextStates.size() == 0) {
   // Must play "pass" move if there are no other moves possible.
   return new GameState(gameState, new Move());
  }

  int v_new = Integer.MIN_VALUE;
  int v_max = 0;
  GameState bestState = nextStates.elementAt(0);

  for(int i = 0; i < nextStates.size(); i++){ 
   v_new = alphabetaSearch(nextStates.elementAt(i));
    if(v_new < v_max ){
      v_max = v_new;
      bestState = nextStates.elementAt(i);
    }
    if (deadline.timeUntil() < 100000) {
      return bestState;
    }
  }
  return bestState;
 }

 private int alphabetaSearch(GameState state){
  int v = 0;
  v = maxValue(state, 0 , Integer.MIN_VALUE, Integer.MAX_VALUE);
  return v;
 }

 private int maxValue(GameState state, int depth, int alpha, int beta){
  
  if (depth == 5 || state.getMove().isEOG()){
    return gamma(state.getNextPlayer() , state);
  }
  Vector<GameState> children = new Vector<GameState>();
  state.findPossibleMoves(children);
  int v = Integer.MIN_VALUE;
 if(state.getNextPlayer() == Constants.CELL_X){
    for(GameState child: children){
      v = Math.max(v, minValue(child, depth+1, alpha, beta));
      //depth++;
      if (v >= beta) {
        return v;
      }
      alpha = Math.max(alpha, v);
    }
  }
  return v;
 }

 private int minValue(GameState state, int depth, int alpha, int beta){
  
  if (depth == 5 || state.getMove().isEOG()){
    return gamma(state.getNextPlayer() , state);
  }
  Vector<GameState> children = new Vector<GameState>();
  state.findPossibleMoves(children);
  int v =Integer.MAX_VALUE;
  if(state.getNextPlayer() == Constants.CELL_O){
    for(GameState child: children){
      v = Math.min(v, maxValue(child, depth+1, alpha, beta));
      //depth++;
      if (v <= alpha) {
        return v;
      }
      beta = Math.min(beta, v);
    }
  }
  return v;
 }

 public int gamma(int player, GameState state) {
  if (state.getMove().isOWin()) return Integer.MIN_VALUE;
  else if (state.getMove().isXWin()) return Integer.MAX_VALUE;
 
  int value = 0;
  // Check middle

    for (int i = 1; i < 3; i++) {
   for (int j = 1; j < 3 ; j++) {
    if (state.at(i,j) == Constants.CELL_X) {
     value += 10;
    }
   }
  }

  

  // Check corners
  if (state.at(0,0) == Constants.CELL_X) {
   value += 5;
  }
  if (state.at(0,3) == Constants.CELL_X) {
   value += 5;
  }
  if (state.at(3,0) == Constants.CELL_X) {
   value += 5;
  }
  if (state.at(3,3) == Constants.CELL_X) {
   value += 5;
  }

  return value;
 }
}