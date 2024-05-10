function sum {
  echo "Enter a number"
  read num
  sum=0
  for((i=0; num>0; i++))
  do
  number=$((num%10))
  sum=$((sum+number))
  num=$((num/10))
  done
  echo $sum
}

sum