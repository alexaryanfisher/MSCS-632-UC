/* Rust Ownership and Borrowing
Code based on YouTube video and Rust Docs [https://www.youtube.com/watch?v=8M0QfLUDaaA |
https://doc.rust-lang.org/rust-by-example/index.html] */
fn main() {
    // Allocation
    let mut own_data = Vec::new();
    for i in 0..25 {
    own_data.push(i);
    }
    //Borrowing, 'own_data' is freed when it goes out of scope.
    {
    let borrow_data = &amp;own_data[3];
    //Checking borrow is valid.
    println!(&quot;Borrowed Data: {}&quot;, borrow_data);
    }

    // Transfering ownership from 'own_data' to 'modified_data' then back to 'own_data'.
    let mut modified_data = own_data;
    for i in 0..modified_data.len() {
    modified_data[i] *= 2;
    }

    // 'own_data'; is no longer valid, 'modified_data' is now the owner
    println!("Modified data length: {}", modified_data.len());

    // 'modified data' is dropped automatically when it goes out of scope.
}