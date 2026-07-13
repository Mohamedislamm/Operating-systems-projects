# Car Wash Simulator

Java simulation of a car wash using the producer-consumer pattern with custom semaphores.

**Requirements:** Java 23+

**Run:** Double-click `run.bat`, or from terminal:

```
run.bat
```

For the built-in test scenario:
```
run.bat --test
```

Or manually:
```
mkdir target\classes
javac -d target/classes src/main/java/org/os/Semaphore.java src/main/java/org/os/Car.java src/main/java/org/os/Pump.java src/main/java/org/os/ServiceStation.java src/main/java/org/os/Main.java
java -cp target/classes org.os.Main --test
```

**Input:** waiting area capacity (1-10), number of pumps, then car IDs like `C1, C2, C3`. The `--test` option runs a built-in sample scenario without prompts.
