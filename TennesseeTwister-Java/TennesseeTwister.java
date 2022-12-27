// **********************************************************************************************
// Program: // Name: Amber Ford

// Program Description:
//      This program makes sure a user is safe to ride the Tennessee Twister with given weight
//
// **********************************************************************************************

import java.util.*;

public class TennesseeTwister {
    public static void main(String[] args) {
        Scanner scnr = new Scanner(System.in);
        double[] userWeight = new double[5];
        loadWeights(userWeight, scnr);
        double totalWeight = displayAndTotalWeights(userWeight);
        displaySafetyMessage(totalWeight,scnr);

    }
    /**
     * loadWeights –
     * This method decides how much money the user earned
     *Precondition: empty array, and scanner
     * @param userWeight  -- array to store weights
     * @param scnr -- scnr to console
     * @return -- nothing
     */
    public static void loadWeights(double userWeight[], Scanner scnr) {
        System.out.println("Enter weight 1:");
        double weight1 = getWeight(scnr);
        userWeight[0] = weight1;
        System.out.println("Enter weight 2:");
        double weight2 = getWeight(scnr);
        userWeight[1] = weight2;
        System.out.println("Enter weight 3:");
        double weight3 = getWeight(scnr);
        userWeight[2] = weight3;
        System.out.println("Enter weight 4:");
        double weight4 = getWeight(scnr);
        userWeight[3] = weight4;
        System.out.println("Enter weight 5:");
        double weight5 = getWeight(scnr);
        userWeight[4] = weight5;

    }
/**
 * getWeight –
 * This method gets weight from user
 *Precondition: weight must be a double
 * @param scnr -- scanner from oonsole
 * @return -- rider weight
 */
    public static double getWeight(Scanner scnr) {
        double riderWeight = 0.0;
        if(scnr.hasNextDouble()){
            riderWeight = scnr.nextDouble();
        }else {
            do {
                System.out.print("Please enter a valid weight: ");
                scnr.nextLine();
                if (scnr.hasNextDouble()) {
                    riderWeight = scnr.nextDouble();
                }
                scnr.nextLine();
            }while (!(scnr.hasNextDouble())) ;
        }
        return riderWeight;
    }
/**
 * displayAndTotalWeights –
 * This method totals user's weights and displays them
 *Precondition: array with weights
 * @param userWeight  -- array containing all of the user's weights
 * @return -- total of weights
 */

    public static double displayAndTotalWeights(double userWeight[]) {
        double weightSum = 0.0;
        System.out.print("You entered: ");
        for (int i = 0; i < userWeight.length; i++) {
            System.out.print(userWeight[i] + " ");
            weightSum += userWeight[i];
        }
        System.out.println();
        System.out.println();
        System.out.println("Total weight: " + weightSum);
        return weightSum;
    }
/**
 * displaySafetyMessage –
 * This method gives a safety message using weights
 * @param totalWeight  -- total of user weight's
 * @return -- nothing
 */

    public static void displaySafetyMessage(double totalWeight,Scanner scnr) {
        char choice;
        if (totalWeight > 900) {
            System.out.println("Ride weight OVER. Tennessee Twister is UNSAFE. DO NOT PROCEED.");

        } else if (totalWeight < 500) {
            System.out.println("Ride weight UNDER. Tennessee Twister is UNSAFE. DO NOT PROCEED.");
            System.out.println();
            System.out.print("Continue (y/n)?");
            choice = scnr.next().charAt(0);
        } else {
            System.out.println("Ride weight GOOD. Tennessee Twister is GOOD TO GO!");
            System.out.println();
            System.out.print("Continue (y/n)?");
            choice = scnr.next().charAt(0);
        }
    }


}
