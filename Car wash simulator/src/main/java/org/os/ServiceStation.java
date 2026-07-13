package org.os;

import java.util.LinkedList;
import java.util.Queue;
import java.util.Scanner;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

/**
 * ServiceStation (Main) class that initializes and manages the simulation
 */
public class ServiceStation {
    private Queue<String> waitingQueue;
    private Semaphore empty;      // Semaphore for empty slots in queue
    private Semaphore full;       // Semaphore for full slots in queue
    private Semaphore pumps;      // Semaphore for service bays (pumps)
    private Object mutex;         // Mutex for queue access
    private int numPumps;
    private Pump[] pumpThreads;
    private ExecutorService pumpExecutor;
    
    public ServiceStation(int queueCapacity, int numPumps) {
        // Validate inputs
        if (queueCapacity < 1 || queueCapacity > 10) {
            throw new IllegalArgumentException("Queue size must be between 1 and 10");
        }
        if (numPumps < 1) {
            throw new IllegalArgumentException("Number of pumps must be at least 1");
        }
        
        this.numPumps = numPumps;
        
        // Initialize shared resources
        this.waitingQueue = new LinkedList<>();
        this.empty = new Semaphore(queueCapacity);  // Initially all slots are empty
        this.full = new Semaphore(0);               // Initially no items in queue
        this.pumps = new Semaphore(numPumps);       // Number of available service bays
        this.mutex = new Object();
        
        // Create pump threads
        this.pumpThreads = new Pump[numPumps];
        this.pumpExecutor = Executors.newFixedThreadPool(numPumps);
        
        // Initialize and start pump threads
        for (int i = 0; i < numPumps; i++) {
            pumpThreads[i] = new Pump(i + 1, waitingQueue, empty, full, pumps, mutex);
            pumpExecutor.submit(pumpThreads[i]);
        }
    }
    
    public void addCar(String carId) {
        Car car = new Car(carId, waitingQueue, empty, full, mutex, numPumps);
        car.start();
    }
    
    public void shutdown() {
        // Stop all pump threads
        for (Pump pump : pumpThreads) {
            pump.stopPump();
        }
        
        // Shutdown executor
        pumpExecutor.shutdown();
        try {
            if (!pumpExecutor.awaitTermination(10, TimeUnit.SECONDS)) {
                pumpExecutor.shutdownNow();
            }
        } catch (InterruptedException e) {
            pumpExecutor.shutdownNow();
            Thread.currentThread().interrupt();
        }
    }
    
    public boolean isQueueEmpty() {
        synchronized (mutex) {
            return waitingQueue.isEmpty();
        }
    }
    
    
    public static void main(String[] args) {
        if (args != null && args.length > 0 && "--test".equalsIgnoreCase(args[0])) {
            runBuiltInTestScenario();
            return;
        }

        runInteractiveScenario();
    }

    private static void runBuiltInTestScenario() {
        ServiceStation station = new ServiceStation(3, 2);
        String[] carIds = {"C1", "C2", "C3", "C4"};

        for (String carId : carIds) {
            station.addCar(carId);
            try {
                Thread.sleep(100);
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
                e.printStackTrace();
            }
        }

        waitForProcessingToFinish(station);
        station.shutdown();

        System.out.println("\n=== Built-in test scenario completed ===");
    }

    private static void runInteractiveScenario() {
        Scanner scanner = new Scanner(System.in);

        try {
            System.out.print("Waiting area capacity: ");
            int queueCapacity = scanner.nextInt();

            System.out.print("Number of service bays (pumps): ");
            int numPumps = scanner.nextInt();

            System.out.print("Cars arriving (order): ");
            scanner.nextLine();
            String carsInput = scanner.nextLine().trim();
            String[] carIds = carsInput.split(",\\s*");

            ServiceStation station = new ServiceStation(queueCapacity, numPumps);

            for (String carId : carIds) {
                carId = carId.trim();
                station.addCar(carId);
                try {
                    Thread.sleep(100);
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                    e.printStackTrace();
                }
            }

            waitForProcessingToFinish(station);
            station.shutdown();

            System.out.println("\n=== All cars processed; simulation ends ===");
        } finally {
            scanner.close();
        }
    }

    private static void waitForProcessingToFinish(ServiceStation station) {
        try {
            while (!station.isQueueEmpty() || station.pumps.availablePermits() < station.numPumps) {
                Thread.sleep(100);
            }

            Thread.sleep(2000);
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
            e.printStackTrace();
        }
    }
}

