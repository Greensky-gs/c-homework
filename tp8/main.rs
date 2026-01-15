use std::fs::File;
use std::io::{BufRead,BufReader,BufWriter,Write};

type Matrix = Vec<Vec<u32>>;
struct Image {
    rows: usize,
    cols: usize,
    matrix: Matrix
}

fn parse_image(path: &String) -> std::io::Result<Image> {
    let file = File::open(path)?;
    let reader = BufReader::new(file);

    let mut image = Image {
        rows: 0,
        cols: 0,
        matrix: vec![]
    };

    let mut max: u16 = 0;
    let mut i: usize = 0;
    for big_line in reader.lines() {
        let line = big_line?;
        if i == 1 {
            let mut parts = line.split_whitespace();

            image.cols = parts.next().unwrap().parse().unwrap();
            image.rows = parts.next().unwrap().parse().unwrap();
        }
        if i == 2 {
            max = line.parse().unwrap();
        }
        if i > 2 {
            if image.matrix.len() < i - 2 {
                image.matrix.push(vec![]);
            }
            let mut parts = line.split_whitespace();

            let mut j: usize = 0;
            while j < image.cols {
                image.matrix[i - 3].push((255 * parts.next().unwrap().parse::<u16>().unwrap() / max).into());
                j+=1;
            }
        }
        i+=1;
    }

    return Ok(image);
}
fn display_matrix(matrix: &Matrix) {
    for row in matrix {
        for col in row {
            print!("{:<3} ", col);
        }
        print!("\n");
    }
}
fn setup_with(matrix: &mut Matrix, value: &u32, rows: &usize, cols: &usize) {
    let mut i = 0;
    while i < *rows {
        (*matrix).push(vec![]);

        let mut j: usize = 0;
        while j < *cols {
            (*matrix)[i].push(*value);
            j+=1;
        }
        i+=1;
    }
}
fn rotate(image: &Image) -> Image {
    let mut img = Image {
        cols: (*image).rows,
        rows: (*image).cols,
        matrix: vec![]
    };
    setup_with(&mut img.matrix, &0, &img.rows, &img.cols);

    let mut i: usize = 0;
    while i < (*image).rows {
        let mut j = 0;
        while j < (*image).cols {
            img.matrix[j][(*image).rows - i - 1] = (*image).matrix[i][j];
            j+=1;
        }
        i+=1;
    }
    return img;
}
fn save(image: &Image, path: &String) -> std::io::Result<()> {
    let file = File::create(path)?;
    let mut writer = BufWriter::new(file);

    writeln!(writer, "P2\n{} {}\n255", image.cols, image.rows)?;

    for row in &(*image).matrix {
        for val in row {
            write!(writer, "{:<3} ", val)?;
        }
        write!(writer, "\n")?;
    }

    return Ok(());
}

fn main() {
    let image: Image;
    match parse_image(&"feep.pgm".to_string()) {
        Ok(img) => image = img,
        Err(_) => return println!("An error occured")
    }

    display_matrix(&image.matrix);

    let rotated = rotate(&image);

    display_matrix(&rotated.matrix);

    match save(&rotated, &"rotated_feep.pgm".to_string()) {
        Ok(_) => println!("Save successful"),
        Err(_) => return println!("Something went wrong")
    }
}
