function zipFile(){
  read -p "Enter the directory path: " directory_path

  read -p "Enter the file extension (e.g., txt): " file_extension

  if [ ! -d "$directory_path" ]; then
    echo "Error: Directory does not exist."
    exit 1
  fi

  zip_file_name="Zipped File"

  files=$(find "$directory_path" -type f -name "*.$file_extension")

  # Check if any files were found
  if [ -z "$files" ]; then
    echo "No files with the extension '$file_extension' found in the directory and its subdirectories."
    exit 1
  fi

  # Compress all the found files into a single zip file
  zip -q "$zip_file_name" $files

  echo "Compression successful. Zip file created: $zip_file_name"


}

zipFile