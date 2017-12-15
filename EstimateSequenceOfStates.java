import java.util.Scanner;
import java.lang.StringBuilder;

public class EstimateSequenceofStates {

    private static Scanner sc = new Scanner(System.in);
    public static void main(String[] args){
        
        double[][] transitionmatrix = readMatrix();
        double[][] emissionmatrix = readMatrix();
        double[][] pi = readMatrix();
        int[] observations = readObservations();

        System.out.println(findSequence(transitionmatrix,emissionmatrix,pi,observations));

    }

    public static String findSequence(double[][] a, double[][] b, double[][] pi, int[] o) {
        
        double[][] delta = new double[a.length][o.length];
        int[][] deltaIndex = new int[a.length][o.length];

		//initialiserar första kolumnen i var delta matris. t.ex på tidpunkt tre kom jag från state 2
        for (int i = 0; i < a.length; i++) {
               delta[i][0] = b[i][o[0]] * pi[0][i];
        }
		// delta innehaller SANNOLIKETEN för vilket state vi kom ifrån 
		// dvs från ett state till ett annat.
		
		//deltaIndex innehåller värdet på state som vi kom ifrån
        for (int t = 1; t < o.length; t++) {
            for (int i = 0; i < a.length; i++) {
                double max = 0;
                int index = 0;
                for (int j = 0; j < a.length; j++) {
                    double value = a[j][i] * delta[j][t-1] * b[i][o[t]];
                    if(max < value) {
                        max = value;
                        index = j;
                    }
                }
                delta[i][t] = max;
                deltaIndex[i][t] = index;
            }
        }

        

        //printMatrix(delta);
		//printMatrixI(deltaIndex);

        double max = 0;
        int max_idx = 0;

        // Find most probable state at the end delta_T(i)
        for (int i = 0; i < a.length; i++) {
            if (max < delta[i][o.length-1]) {
                max = delta[i][o.length-1];
                max_idx = i;
            }
        }

        StringBuilder sb = new StringBuilder();
        sb.append(max_idx + " "); // lägger till i slutet

        // Backtrack vi kollar på sista tidpunkten med maxidx
        for (int t = o.length-1; t > 0; t--) {
            max_idx = deltaIndex[max_idx][t];
            sb.insert(0, max_idx + " "); // insert 0 lägger in element på plats 0
        }

        return sb.toString();
    }

    public static int[] readObservations() {
        int n = sc.nextInt();
        int[] observations = new int[n];
        for (int i = 0; i < n; i++) {
            observations[i] = sc.nextInt();
        }
        return observations;
    }

    public static double[][] readMatrix() {
        int rows = 0;
        int columns = 0;
        if (sc.hasNextInt())
            rows = sc.nextInt();
        if (sc.hasNextInt())
            columns = sc.nextInt();

        double[][] matrix = new double[rows][columns];
        for (int i = 0; i < rows; i++){
            for (int j = 0; j < columns; j++){
                matrix[i][j] = Double.parseDouble(sc.next());
            }
        }
        return matrix;
    }

        public static void printMatrix(double[][] matrix) {
        System.out.println(matrix.length + " " + matrix[0].length + " ");
        for (int i = 0; i < matrix.length ; i++) {
            for (int j = 0; j < matrix[0].length ; j++) {
                System.out.print(matrix[i][j] + " ");
            }
            System.out.println();
        }
        System.out.println();
    }
	        public static void printMatrixI(int[][] matrix) {
        System.out.println(matrix.length + " " + matrix[0].length + " ");
        for (int i = 0; i < matrix.length ; i++) {
            for (int j = 0; j < matrix[0].length ; j++) {
                System.out.print(matrix[i][j] + " ");
            }
            System.out.println();
        }
        System.out.println();
    }

}