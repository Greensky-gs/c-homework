use std::io::{stdin,stdout,Write};

fn main() {
    print!("Entrez une annee : ");
    let _ = stdout().flush();

    let mut res = String::default();
    let year: u64;
    match stdin().read_line(&mut res) {
        Ok(_) => {
            match res.trim().parse::<u64>() {
                Ok(n) => year = n,
                Err(_) => { return println!("Votre annee n'a pas pu etre parsee correctement"); }
            }
        },
        Err(_) => { return println!("Votre anee n'a pas pu etre parsee correctement"); }
    }

    println!("\x1b[33m{}\x1b[0m {}", year, if year % 400 == 0 || (year % 4 == 0 && year % 100 != 0) { "est bissextile" } else {"n'est pas bissextile"} );
}
