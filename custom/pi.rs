use std::io::{stdin,stdout,Write};
use rand::{Rng};
use rand::rngs::ThreadRng;

fn get_repeats() -> Option<u64> {
    print!("Entrez le nombre de repetitions : ");
    let _ = stdout().flush();

    let mut line = String::from("");
    match stdin().read_line(&mut line) {
        Ok(_) => {
            match line.trim().parse::<u64>() {
                Ok(n) => return Some(n),
                Err(_) => {return None;}
            }
        },
        Err(_) => {return None;}
    }
}
fn get_pos(thread: &mut ThreadRng) -> (f64, f64) {
   return ((*thread).random_range(0.0..1.0), (*thread).random_range(0.0..1.0));
}
fn main() {
    let repeats: u64;
    match get_repeats() {
        Some(n) => repeats = n,
        None => {
            return println!("Cannot parse your number");
        }
    }

    let mut thread = rand::rng();

    let mut i: u64 = 0;
    let mut inside: u64 = 0;

    while i < repeats {
        let res = get_pos(&mut thread);
        if res.0 * res.0 + res.1 * res.1 <= 1_f64 {
            inside+=1;
        }
        i+=1;
    }

    let fourth_pi: f64 = inside as f64 / repeats as f64;
    let pi: f64 = fourth_pi * 4.0;

    println!("Nombre de points dans le cercle : \x1b[34m{}\x1b[0m\nNombre total de points          : \x1b[34m{}\x1b[0m.", inside, repeats);
    println!("Une valeur approchee de \x1b[32mpi\x1b[0m avec \x1b[34m{}\x1b[0m repetitions est : \x1b[33m{}\x1b[0m", repeats, pi);
}
