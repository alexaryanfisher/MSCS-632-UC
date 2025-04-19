// Data Processing System, Go.
package main

import (
	"fmt"
	"log"
	"math/rand"
	"os"
	"sync"
	"time"
	"runtime"
	"strconv"
	"strings"
)

// Task structure
type Task struct {
	ID       int
	Data	 string
}

// Result structure
type Result struct {
	TaskID       int
	ResultData   string
}

// Processing time
func (task *Task) process() string {
	// Simulate processing time
	delay := time.Duration(rand.Intn(100)) * time.Millisecond
	time.Sleep(delay)
	return fmt.Sprintf("Processed data for task %d: %s" , task.ID, task.Data)
	}

// Worker tasks
func worker(tasks <-chan Task, results chan<- Result, wg *sync.WaitGroup) {
	defer wg.Done()
	log.Printf("Worker %s started", getgoRoutineID())
	for task := range tasks {
		processingResult := task.process()
		result := Result{TaskID: task.ID, ResultData: processingResult}
		results <- result
		log.Printf("Worker %s processed task %d", getgoRoutineID(), task.ID)
	}
	log.Printf("Worker %s finished", getgoRoutineID())
}

// Get the ID of the current routine
func getgoRoutineID() uint64 {
	var buf [64]byte
	n := runtime.Stack(buf[:], false)
	idField := strings.Fields(strings.TrimPrefix(string(buf[:n]), "goroutine"))[0]
	id, err := strconv.ParseUint(idField, 10, 64)
	// Error handling
	if err != nil {
		panic(fmt.Sprintf("Failed to get goroutine ID: %v", err))
	}
	return id
}

// Main function
func main() {
	numWorkers := 10
	numTasks := 40
	tasks := make(chan Task, numTasks)
	results := make(chan Result, numTasks)
	var wg sync.WaitGroup


	// Start worker routines
	for i := 0; i < numWorkers; i++ {
		wg.Add(1)
		go worker(tasks, results, &wg)
	}

	// Generate tasks
	for i := 0; i < numTasks; i++ {
		task := Task{ID: i, Data: fmt.Sprintf("Data %d", i)}
		tasks <- task
		log.Printf("Main routine created task %d", i)
	}
	// Close the tasks channel, signaling no more tasks will be sent.
	close(tasks)

	// Wait for all workers to finish/ Collect all results
	go func() {
		wg.Wait()
		close(results)
	}()

	// Collect results and save to file
	outputFile := "results_go.txt"
	file, err := os.Create(outputFile)
	// Error handling, Check if the file was created successfully
	if err != nil {
		log.Fatalf("Failed to create output file: %v", err)
	}
	defer func() {
		if err := file.Close(); err != nil {
			log.Fatalf("Failed to close output file: %v", err)
		}
	}()

	log.Printf("Main routine started collecting results to file...")
	for result := range results {
		_, err := file.WriteString(fmt.Sprintf("%+v\n", result))
		// Error handling, Check if the result was written successfully.
		if err != nil {
			log.Fatalf("Failed to write result to file: %v", err)
		}
	}
	// Confirming printing results to output file.
	log.Printf("Results have been written to %s", outputFile)
	log.Printf("Main routine finished")
}
