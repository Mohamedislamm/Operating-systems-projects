package org.os;

/**
 * Main class - Entry point for the Car Wash and Gas Station simulation
 * This is a Producer-Consumer problem using Bounded Buffer pattern
 */
public class Main {
    public static void main(String[] args) {
        // Delegate to ServiceStation main method
        ServiceStation.main(args);
    }
}