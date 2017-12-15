import java.util.Arrays;
import java.util.Scanner;

/**
 * Created by Mona on 2016-09-07.
 */
public class ProbabilityofEmissionSequence {
    public static void main(String[] args){
        //Kattio io = new Kattio(System.in, System.out);
        Scanner sc = new Scanner(System.in);
        
        int rowsInTransitionMatrix = sc.nextInt();
        int colsInTransitionMatrix = sc.nextInt();
        double[][] transitionmatrix = new double[rowsInTransitionMatrix][colsInTransitionMatrix];
        for(int i = 0; i < rowsInTransitionMatrix; i++){
            for(int j = 0; j < colsInTransitionMatrix; j++){
                transitionmatrix[i][j] = Double.parseDouble(sc.next());
            }
        }

        int rowsInEmissionMatrix = sc.nextInt();
        int colsInEmissionMatrix = sc.nextInt();
        double[][] emissionmatrix = new double[rowsInEmissionMatrix][colsInEmissionMatrix];

        for(int x = 0; x < rowsInEmissionMatrix; x++){
            for(int y = 0; y < colsInEmissionMatrix; y++){
                emissionmatrix[x][y] = Double.parseDouble(sc.next());
            }
        }

        int tmp1 = sc.nextInt();
        int inInitialVectorLength = sc.nextInt();
        double[] initial = new double[inInitialVectorLength];
        for(int k = 0; k < inInitialVectorLength; k++ ){
            initial[k] = Double.parseDouble(sc.next());
        }
        
        int nrOfEmissions = sc.nextInt();
        int[] emissionSequence = new int[nrOfEmissions];
        for(int y = 0; y < nrOfEmissions; y++ ){
            emissionSequence[y] = sc.nextInt();
        }

        sc.close();

        
        double[] alphaVector = new double[inInitialVectorLength];
        alphaVector = computeNextAlpha(initial, emissionmatrix, emissionSequence[0], inInitialVectorLength);

        double[] alphaTimesTM = new double[inInitialVectorLength];
        
        for(int value = 1; value < emissionSequence.length; value++){
            alphaTimesTM = computeAlphaTimesTransitionMatrix(transitionmatrix, alphaVector, inInitialVectorLength);
            alphaVector = computeNextAlpha(alphaTimesTM, emissionmatrix, emissionSequence[value], inInitialVectorLength);
        }
        
        double probOfObservationSequence = 0.0;
        probOfObservationSequence = sumElemsInAlpha(alphaVector);

        System.out.println(probOfObservationSequence);
    }

    public static double sumElemsInAlpha(double[] alphaVector){
        double sum = 0.0;
        for(int i = 0; i < alphaVector.length; i++){
            sum += alphaVector[i];
        }
        return sum;
    }
    public static double[] computeAlphaTimesTransitionMatrix(double[][] transitionmatrix, double[] alphaVector, int inInitialVectorLength){

        double value = 0;
        double[] alphaTimesTM = new double[inInitialVectorLength];
        // alpha2 = alpha1 * A
        for(int ct = 0; ct < transitionmatrix.length; ct++){
            for(int rt = 0; rt < transitionmatrix.length; rt++){
                value = alphaVector[rt] * transitionmatrix[rt][ct] ;
                alphaTimesTM[ct] += value;
            }
        }

        return alphaTimesTM;
    }

    public static double[] computeNextAlpha(double[] alphaTimesTM, double[][] emissionmatrix, int emissionSequenceValue, int inInitialVectorLength){
        double value = 0;
        double[] nextAlpha = new double[inInitialVectorLength];
        // alpha2 = alpha1 * A
        for(int c = 0; c < emissionmatrix[0].length; c++){
            for(int r = 0; r < emissionmatrix.length; r++){
                if(c == emissionSequenceValue){
                    value = alphaTimesTM[r] * emissionmatrix[r][c];
                    nextAlpha[r] = value;
                }
            }
        }

        return nextAlpha;
    }
}