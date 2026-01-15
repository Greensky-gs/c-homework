use rustyline::DefaultEditor;

fn main() {
    let mut rl = DefaultEditor::new().unwrap();
    let expression;

    match rl.readline("Entrez votre texte : ") {
        Ok(t) => expression = t.to_string().clone(),
        Err(_) => {
            println!("Erreur de lecture");
            return;
        }
    }

    let mut i: usize = 0;
    let mut voyelles: usize = 0;

    while i < expression.len() {
        let c = expression.chars().nth(i).unwrap();

        match c {
            'a' | 'e' | 'u' | 'i' | 'o' | 'y' => {
                voyelles+=1;
            },
            _ => {}
        }

        i+=1;
    }

    println!("Il y a {} lettres totales, et {} voyelles", expression.len(), voyelles);

    return;
}
