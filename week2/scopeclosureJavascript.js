/* Javascript - Scope and Closures
Code Based from GeeksforGeeks[https://www.geeksforgeeks.org/difference-between-scope-and-closures-in-javascript/] */

function outerFunction(x){
    return function innerFunction(y){
        return x + y; // 'x' captured from outer scope.
    };
}

const closureInstance = outerFunction(5);
const result = closureInstance(3);
console.log(result) // Output : 8

function createCounter(){
    let count = 0;
    return function increment(){
        count++;
        return count;
    };
}

const counter = createCounter();
console.log(counter()); // First Count : 1
console.log(counter()); // Second Count : 2
console.log(counter()); // Third Count : 3