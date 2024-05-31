DIRECTORY=$1
DAYS=$2

if [ ! -d "$DIRECTORY" ]; then
    echo "Error: Directory $DIRECTORY does not exist."
    exit 1
fi

FILES=$(find "$DIRECTORY" -type f -mtime -"$DAYS")

if [ -z "$FILES" ]; then
    echo "No files found that were modified in the last $DAYS days."
else
    echo "Files modified in the last $DAYS days:"
    echo "$FILES"
    echo "$FILES" > sp22-bse-119
    echo "The list of files has been saved to sp22-bse-119."
fi
