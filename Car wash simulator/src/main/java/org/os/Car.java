package org.os;

import java.util.Queue;

/**
 * Car (Producer) class that produces cars into the waiting queue
 */
public class Car extends Thread {
    private String carId;
    private Queue<String> waitingQueue;
    private Semaphore empty;      // Semaphore for empty slots in queue
    private Semaphore full;       // Semaphore for full slots in queue
    private Object mutex;         // Mutex for queue access
    private int numPumps;         // Number of pumps to determine if car will wait
    
    public Car(String carId, Queue<String> waitingQueue, Semaphore empty, 
               Semaphore full, Object mutex, int numPumps) {
        this.carId = carId;
        this.waitingQueue = waitingQueue;
        this.empty = empty;
        this.full = full;
        this.mutex = mutex;
        this.numPumps = numPumps;
    }
    
    @Override
    public void run() {
        try {
            System.out.println(carId + " arrived");
            
            // Wait for empty slot in queue (producer waits on empty)
            empty.acquire();
            
            // Acquire mutex to access queue
            int queueSizeAfterAdd = 0;
            synchronized (mutex) {
                waitingQueue.offer(carId);
                queueSizeAfterAdd = waitingQueue.size();
            }
            
            // Signal that queue has one more item (producer signals full)
            full.release();
            
            // Give pumps time to claim cars before checking if this one is still waiting
            Thread.sleep(queueSizeAfterAdd > numPumps ? 300 : 350);
            synchronized (mutex) {
                if (waitingQueue.contains(carId)) {
                    System.out.println(carId + " arrived and waiting");
                }
            }
            
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
            e.printStackTrace();
        }
    }
}

