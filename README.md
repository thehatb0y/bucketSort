# Bucket Sort Implementation and Fibonacci Discussion using OpenMP

## Professor
GERSON GERALDO HOMRICH CAVALHEIRO

## Student
Mateus C S Santos - 14101915

### Bucket Sort Algorithm

This repository contains a C implementation of the Bucket Sort algorithm using data structures and linked lists. Linked lists were chosen to optimize memory usage, avoiding waste and allowing flexibility in the number of elements in each bucket.

The code creates a list and allocates the user-specified number of elements. The elements are distributed into buckets, the quantity of which is also user-defined. The algorithm's execution can be parallelized, and tests were performed to evaluate the impact of parallelism. Results indicate that for smaller lists, the cost of parallelism may outweigh its benefits, while for larger lists (above 100,000 elements), parallelism shows significant improvements.

### Discussion on Fibonacci using OpenMP

In addition to Bucket Sort, the repository includes a discussion on implementing Fibonacci using OpenMP. Surprisingly, the Fibo-1 code, which parallelizes r1 and r2, had an almost double runtime compared to Fibo-2, which executes r2 sequentially in the same context. The analysis suggests that the overhead of task creation can impact performance, and in less complex cases, it is more efficient to take advantage of an existing task's context.

### How to Run

1. Compile the code using a C compiler compatible with OpenMP.
2. Execute the program, providing the necessary parameters such as the number of buckets, the maximum list size, and the parallelism option.

### Results and Considerations

The test results align with expectations, demonstrating the importance of evaluating the cost-effectiveness of parallelism. The choice of the Bubble Sort algorithm was made for its ease of implementation in linked lists, but the code has been modularized to facilitate the substitution of other sorting algorithms in the future.

### GitHub

The source code is available on GitHub: [Bucket Sort Repository](https://github.com/thehatb0y/bucketSort/tree/main)

### Contact

For more information or questions, contact the code author: Mateus C S Santos - [GitHub Profile](https://github.com/thehatb0y)

---

**Note:** This README provides an overview of the project, execution instructions, and obtained results. Be sure to review the source code for a detailed understanding of the implementation.
