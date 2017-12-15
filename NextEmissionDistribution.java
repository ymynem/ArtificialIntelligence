import java.util.Arrays;
import java.util.Scanner;

/**
 * Created by Mona on 2016-09-07.
 */
public class NextEmissionDistribution {
    public static void main(String[] args){
        //Kattio io = new Kattio(System.in, System.out);
        Scanner sc = new Scanner(System.in);
        
        int rows = sc.nextInt();
        int columns = sc.nextInt();
        double[][] transitionmatrix = new double[rows][columns];
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < columns; j++){
                transitionmatrix[i][j] = Double.parseDouble(sc.next());
            }
        }

        int rowse = sc.nextInt();
        int columnse = sc.nextInt();
        double[][] emissionmatrix = new double[rowse][columnse];

        for(int x = 0; x < rowse; x++){
            for(int y = 0; y < columnse; y++){
                emissionmatrix[x][y] = Double.parseDouble(sc.next());
            }
        }

        int a = sc.nextInt();
        int cols = sc.nextInt();
        double[] initial = new double[cols];
        for(int k = 0; k < cols; k++ ){
            initial[k] = Double.parseDouble(sc.next());
        }
        
        sc.close();
        //carje rad och varje column i andra 

        // A' = initial * A 
        double value1 = 0;
        double[] nyA = new double[columns];
        int counter1 = 0;
        for(int c = 0; c < transitionmatrix.length; c++){
            for(int r = 0; r < transitionmatrix[c].length; r++){
                value1 = initial[r] * transitionmatrix[r][c];
                nyA[c] += value1;
            }
        }

        double value2 = 0;
        double[] nyB = new double[columnse];
        int counter = 0;
        // answer = A' * B
        for(int ct = 0; ct < emissionmatrix[0].length; ct++){
            for(int rt = 0; rt < emissionmatrix.length; rt++){
                value2 = nyA[rt] * emissionmatrix[rt][ct] ;
                nyB[counter] += value2;
            }
            counter++;
        }

        int nrOfRows = 1;
        int nrOfColumns = 0;

        for(int e = 0; e < nyB.length; e ++ ) {
            nrOfColumns += 1; 
        }
        System.out.print(nrOfRows + " " + nrOfColumns +" ");
        for(int el = 0; el < nyB.length; el++){
             System.out.print(nyB[el] + " ");
        }
        System.out.println();
    }

}
