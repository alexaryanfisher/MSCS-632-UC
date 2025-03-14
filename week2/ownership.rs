// Rust Ownership and Borrowing
// Code based on YouTube video and Rust Docs [https://www.youtube.com/watch?v=8M0QfLUDaaA | https://doc.rust-lang.org/rust-by-example/index.html]

fn main(){
    {
        //Muttable variable set to a vector.
        let mut data = Vec::new();
        for i in 0..1000 {
            data.push(i);
        }
    }
    // When data goes out of scope, it will be dropped automatically.

    //Setting variable to a string.
    let own_string = String::from ("Programming is fun!");
    //Setting variable to borrow reference from own_string without taking ownership.
    let borrow_string = &own_string;

    //Borrowed string is outputed.
    println!("{}", borrow_string); 

    //Owned String's memory is freed when it goes out of scope.
}