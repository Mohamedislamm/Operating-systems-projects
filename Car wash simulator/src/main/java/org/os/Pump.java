package org.os;

import java.util.Queue;

/**
 * Pump (Consumer) class that consumes cars from the waiting queue
 */
public class Pump extends Thread {
    private int pumpId;
    private Queue<String> waitingQueue;
    private Semaphore empty;      // Semaphore for empty slots in queue
    private Semaphore full;       // Semaphore for full slots in queue
    private Semaphore pumps;      // Semaphore for service bays (pumps)
    private Object mutex;         // Mutex for queue access
    private volatile boolean running = true;
    
    public Pump(int pumpId, Queue<String> waitingQueue, Semaphore empty,
                Semaphore full, Semaphore pumps, Object mutex) {
        this.pumpId = pumpId;
        this.waitingQueue = waitingQueue;
        this.empty = empty;
        this.full = full;
        this.pumps = pumps;
        this.mutex = mutex;
    }
    
    public void stopPump() {
        running = false;
        interrupt();
    }
    
    @Override
    public void run() {
        while (running) {
            try {
                // Wait for a car in the queue (consumer waits on full)
                full.acquire();
                
                // Acquire mutex to access queue
                String carId;
                synchronized (mutex) {
                    carId = waitingQueue.poll();
                }
                
                if (carId != null) {
                    // Acquire a service bay (pump)
                    pumps.acquire();
                    
                    System.out.println("Pump " + pumpId + ": " + carId + " Occupied");
                    
                    // Small delay to allow "arrived and waiting" messages to appear
                    Thread.sleep(100);
                    
                    System.out.println("Pump " + pumpId + ": " + carId + " login");
                    System.out.println("Pump " + pumpId + ": " + carId + " begins service at Bay " + pumpId);
                    
                    // Simulate service time (random between 1-3 seconds for faster simulation)
                    Thread.sleep((long)(Math.random() * 2000 + 1000));
                    
                    System.out.println("Pump " + pumpId + ": " + carId + " finishes service");
                    System.out.println("Pump " + pumpId + ": Bay " + pumpId + " is now free");
                    
                    // Release the service bay
                    pumps.release();
                    
                    // Signal that queue has one more empty slot (consumer signals empty)
                    empty.release();
                }
                
            } catch (InterruptedException e) {
                if (!running) {
                    break; // Normal shutdown
                }
                Thread.currentThread().interrupt();
                e.printStackTrace();
            }
        }
    }
}

