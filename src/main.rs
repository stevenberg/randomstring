use clap::Parser;
use rand::distributions::Alphanumeric;
use rand::{thread_rng, Rng};

#[derive(Parser)]
#[clap(author, version, about, long_about = None)]
struct Args {
    #[clap(
        short = 's',
        long,
        help = "Number of characters per segment",
        value_parser,
        default_value_t = 4
    )]
    segment_size: usize,

    #[clap(
        short = 'c',
        long,
        help = "Number of segments",
        value_parser,
        default_value_t = 4
    )]
    segment_count: usize,

    #[clap(short, long, help = "Omit dashes between segments", value_parser)]
    no_dashes: bool,
}

fn main() {
    let args = Args::parse();

    let string = thread_rng()
        .sample_iter(&Alphanumeric)
        .take(args.segment_size * args.segment_count)
        .map(char::from)
        .collect::<Vec<char>>()
        .chunks(args.segment_size)
        .map(|c| c.iter().collect())
        .collect::<Vec<String>>()
        .join(if args.no_dashes { "" } else { "-" });

    println!("{}", string);
}
