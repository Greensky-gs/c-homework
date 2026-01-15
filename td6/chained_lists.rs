use std::fmt::Display;
use std::cmp::PartialEq;

struct Cell<T: Display + PartialEq> {
    value: T,
    next: Option<Box<Cell<T>>>
}
struct ChainedList<T: Display + PartialEq> {
    head: Option<Box<Cell<T>>>,
}

impl<T: Display + PartialEq> Cell<T> {
    fn display(&mut self) {
        print!("{}", self.value);
        match &mut self.next {
            Some(c) => {
                print!(", ");
                c.display();
            },
            None => {}
        }
    }

    fn link(&mut self, other: Cell<T>) {
        match &mut self.next {
            Some(c) => c.link(other) ,
            None => self.next = Some(Box::new(other))
        }
    }
}

impl<T: Display + PartialEq> ChainedList<T> {
    fn new() -> ChainedList<T> {
        return ChainedList {
            head: None,
        }
    }

    fn display(&mut self) {
        print!("[");

        match &mut self.head {
            Some(h) => h.display(),
            None => {}
        }

        print!("]\n");
    }

    fn append(&mut self, val: T) {
        let cell = Cell {
            value: val,
            next: None
        };

        match &mut self.head {
            None => self.head = Some(Box::new(cell)),
            Some(c) => c.link(cell)
        }
    }
    fn size(&self) -> usize {
        let mut count: usize = 0;

        let mut current = &self.head;

        while let Some(node) = current {
            count+=1;

            current = &node.next;
        }

        return count;
    }
    fn queue(&self) -> Option<&T> {
        let mut current = &self.head;

        while let Some(node) = current {
            if node.next.is_none() {
                return Some(&node.value);
            }
            current = &node.next;
        }
        return None;
    }

    fn prepend(&mut self, value: T) {
        let new_node = Box::new(Cell {
            value,
            next: self.head.take()
        });
        self.head = Some(new_node);
    }
}

fn main() {
    let mut list = ChainedList::<u8>::new();

    list.append(2);

    println!("Size = {}", list.size());

    list.display();

    list.append(4);
    list.prepend(255);
    list.append(5);

    list.display();

    println!("Size = {}", list.size());

    println!("Value of queue : {}", list.queue().unwrap());
}
