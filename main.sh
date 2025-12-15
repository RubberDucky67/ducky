# PALIN
: <<'comment'
input string
length = size of string
for i = 0 to length - 1
    store string[i] in array[i]
flag = true
for i = 0 to (length / 2) - 1
    if array[i] ≠ array[length - i - 1]
        flag = false
        break
if flag is true
    print "Palindrome"
else
    print "Not Palindrome"
comment
: <<'comment'
#!/bin/bash
echo "Enter a string:"
read str
len=${#str}
for ((i=0; i<len; i++))
do
    arr[$i]=${str:$i:1}
done
flag=1
for ((i=0; i<len/2; i++))
do
    if [ "${arr[$i]}" != "${arr[$((len-i-1))]}" ]
    then
        flag=0
        break
    fi
done
if [ $flag -eq 1 ]
then
    echo "Palindrome"
else
    echo "Not Palindrome"
fi
comment

# BUBBLE
: <<'comment'
input n
input array of n elements
for i = 0 to n-1
    for j = 0 to n-i-2
        if array[j] > array[j+1]
            swap array[j] and array[j+1]
print sorted array
comment
: <<'comment'
#!/bin/bash
echo "Enter numbers separated by space:"
read -a arr
n=${#arr[@]}
for ((i=0; i<n; i++))
do
    for ((j=0; j<n-i-1; j++))
    do
        if [ ${arr[j]} -gt ${arr[$((j+1))]} ]; then
            temp=${arr[j]}
            arr[j]=${arr[$((j+1))]}
            arr[$((j+1))]=$temp
        fi
    done
done
echo "Sorted numbers: ${arr[@]}"
comment

# INSERTION
: <<'comment'
input array
n = size of array
for i = 1 to n-1
    key = array[i]
    j = i - 1
    while j >= 0 and array[j] > key
        array[j+1] = array[j]
        j = j - 1
    array[j+1] = key
print array
comment
: <<'comment'
#!/bin/bash
echo "Enter numbers separated by space:"
read -a arr
n=${#arr[@]}
for ((i=1;i<n;i++))
do
    key=${arr[i]}
    j=$((i-1))
    while [ $j -ge 0 ] && [ ${arr[j]} -gt $key ]
    do
        arr[$((j+1))]=${arr[j]}
        j=$((j-1))
    done
    arr[$((j+1))]=$key
done
echo "Sorted array:"
echo "${arr[@]}"
comment

# SELECTION
: <<'comment'
input array
n = size of array
for i = 0 to n-1
    min = i
    for j = i+1 to n-1
        if array[j] < array[min]
            min = j
    swap array[i] and array[min]
print array
comment
: <<'comment'
#!/bin/bash
echo "Enter numbers separated by space:"
read -a arr
n=${#arr[@]}
for ((i=0;i<n;i++))
do
    min=$i
    for ((j=i+1;j<n;j++))
    do
        if [ ${arr[j]} -lt ${arr[min]} ]
        then
            min=$j
        fi
    done
    temp=${arr[i]}
    arr[i]=${arr[min]}
    arr[min]=$temp
done
echo "Sorted array:"
echo "${arr[@]}"
comment

# QUICK
: <<'comment'
procedure quick_sort(array)
    if size of array ≤ 1
        return array
    pivot = first element
    left = empty list
    right = empty list
    for each element except pivot
        if element ≤ pivot
            add to left
        else
            add to right
    return quick_sort(left) + pivot + quick_sort(right)
input array
call quick_sort
print sorted array
comment
: <<'comment'
#!/bin/bash
echo "Enter numbers separated by space:"
read -a arr
quick_sort() {
    local a=("$@")
    local n=${#a[@]}
    if [ $n -le 1 ]; then
        echo "${a[@]}"
        return
    fi
    pivot=${a[0]}
    left=()
    right=()
    for ((i=1;i<n;i++))
    do
        if [ ${a[i]} -le $pivot ]; then
            left+=(${a[i]})
        else
            right+=(${a[i]})
        fi
    done
    left_sorted=($(quick_sort "${left[@]}"))
    right_sorted=($(quick_sort "${right[@]}"))
    echo "${left_sorted[@]} $pivot ${right_sorted[@]}"
}
sorted=($(quick_sort "${arr[@]}"))
echo "Sorted array:"
echo "${sorted[@]}"
comment

# MERGE
: <<'comment'
procedure merge_sort(array)
    if size of array ≤ 1
        return array
    divide array into left and right halves
    left = merge_sort(left)
    right = merge_sort(right)
    return merge(left, right)
procedure merge(left, right)
    result = empty list
    while left and right not empty
        if left[0] ≤ right[0]
            add left[0] to result
        else
            add right[0] to result
    add remaining elements to result
    return result
input array
call merge_sort
print sorted array
comment
: <<'comment'
#!/bin/bash
echo "Enter numbers separated by space:"
read -a arr
merge() {
    local left=("$@")
    local mid=$(( ${#left[@]} / 2 ))
    local right=("${left[@]:$mid}")
    left=("${left[@]:0:$mid}")
    result=()
    i=0
    j=0
    while [ $i -lt ${#left[@]} ] && [ $j -lt ${#right[@]} ]
    do
        if [ ${left[i]} -le ${right[j]} ]; then
            result+=(${left[i]})
            i=$((i+1))
        else
            result+=(${right[j]})
            j=$((j+1))
        fi
    done
    result+=("${left[@]:$i}")
    result+=("${right[@]:$j}")
    echo "${result[@]}"
}
merge_sort() {
    local a=("$@")
    local n=${#a[@]}
    if [ $n -le 1 ]; then
        echo "${a[@]}"
        return
    fi
    mid=$((n/2))
    left=($(merge_sort "${a[@]:0:$mid}"))
    right=($(merge_sort "${a[@]:$mid}"))
    merge "${left[@]}" "${right[@]}"
}
sorted=($(merge_sort "${arr[@]}"))
echo "Sorted array:"
echo "${sorted[@]}"
comment

# STUDENT
: <<'comment'
101 Rahul 92
102 Sneha 78
103 Aman 65
104 Pooja 55
comment
: <<'comment'
print "Student Report"
for each line in students.txt
    read roll_number, name, marks
    if marks ≥ 90
        grade = "A"
    else if marks ≥ 75
        grade = "B"
    else if marks ≥ 60
        grade = "C"
    else
        grade = "D"
    print roll_number, name, marks, grade
end for
comment
: <<'comment'
#!/bin/bash
echo "Student Report"
awk '{
    if ($3 >= 90) grade="A"
    else if ($3 >= 75) grade="B"
    else if ($3 >= 60) grade="C"
    else grade="D"
    print "Roll No:", $1, "Name:", $2, "Marks:", $3, "Grade:", grade
}' students.txt
comment

# EMPLOYEE
: <<'comment'
201 Arjun 60000
202 Neha 42000
203 Ramesh 28000
204 Kavya 51000
comment
: <<'comment'
print "Employee Report"
for each line in employee.txt
    read emp_id, name, salary
    if salary ≥ 50000
        category = "High"
    else if salary ≥ 30000
        category = "Medium"
    else
        category = "Low"
    print emp_id, name, salary, category
end for
comment
: <<'comment'
#!/bin/bash
echo "Employee Report"
awk '{
    if ($3 >= 50000) category="High"
    else if ($3 >= 30000) category="Medium"
    else category="Low"
    print "Emp ID:", $1, "Name:", $2, "Salary:", $3, "Category:", category
}' employee.txt
comment

# COMMANDS
: <<'comment'
1. Change your password to a password you would like to use for the remainder of the semester.
$ passwd

2. Display the system’s date.
$ date

3. Count the number of lines in the /etc/passwd file.
$ wc -l /etc/passwd

4. Find out who else is on the system.
$ who

5. Direct the output of the man pages for the date command to a file named mydate.
$ man date > mydate

6. Create a subdirectory called mydir.
$ mkdir mydir

7. Move the file mydate into the new subdirectory.
$ mv mydate mydir

8. Go to the subdirectory mydir and copy the file mydate to a new file called ourdate.
$ cd mydir  
$ cp mydate ourdate

9. List the contents of mydir.
$ ls

10. Do a long listing on the file ourdate and note the permissions.
$ ls -l ourdate

11. Display the name of the current directory starting from the root.
$ pwd

12. Move the files in the directory mydir back to the HOME directory.
$ mv * $HOME

13. List all the files in your HOME directory.
$ ls $HOME

14. Display the first 5 lines of mydate.
$ head -n 5 mydate

15. Display the last 8 lines of mydate.
$ tail -n 8 mydate

16. Remove the directory mydir.
$ cd ..  
$ rmdir mydir

17. Redirect the output of the long listing of files to a file named list.
$ ls -l > list

18. Select any 5 capitals of states in India and enter them in a file named capitals
1. Choose 5 more capitals and enter them in a file named capitals
2. Choose 5 more capitals and enter them in a file named capitals
3. Concatenate all 3 files and redirect the output to a file named capitals.
$ echo -e "Mumbai\nChennai\nBangalore\nHyderabad\nKolkata" > capitals1  
$ echo -e "Bhopal\nJaipur\nLucknow\nPatna\nRanchi" > capitals2  
$ echo -e "Shimla\nDehradun\nDispur\nPanaji\nThiruvananthapuram" > capitals3  
$ cat capitals1 capitals2 capitals3 > capitals

19. Concatenate the file capitals2 at the end of file capitals.
$ cat capitals2 >> capitals

20. Redirect the file capitals as an input to the command “wc –l”.
$ wc -l < capitals

21. Give read and write permissions to all users for the file capitals.
$ chmod a+rw capitals

22. Give read permissions only to the owner of the file capitals. Open the file, make some changes and try to save it. What happens?
$ chmod 400 capitals  
$ nano capitals

23. Create an alias to concatenate the 3 files capitals1, capitals2, capitals3 and redirect the output to a file named capitals. Activate the alias and make it run.
$ alias makecapitals='cat capitals1 capitals2 capitals3 > capitals'  
$ makecapitals

24. What are the environment variables PATH, HOME and TERM set to on your terminal?
$ echo $PATH  
$ echo $HOME  
$ echo $TERM

25. Find out the number of times the string “the” appears in the file mydate.
$ grep -o "the" mydate | wc -l

26. Find out the line numbers on which the string “date” exists in mydate.
$ grep -n "date" mydate

27. Print all lines of mydate except those that have the letter “i” in them.
$ grep -v "i" mydate

28. Create the file monotonic as follows: ^a?b?b?c?…………..x?y?z$
Run the egrep command for monotonic against /usr/dict/words and search for all 4 letter words.
$ echo "^a?b?b?c?...x?y?z$" > monotonic  
$ egrep '^....$' /usr/share/dict/words

29. List 5 states in north east India in a file mystates. List their corresponding capitals in a file mycapitals. Use the paste command to join the 2 files.
$ echo -e "Assam\nMeghalaya\nManipur\nMizoram\nTripura" > mystates  
$ echo -e "Dispur\nShillong\nImphal\nAizawl\nAgartala" > mycapitals  
$ paste mystates mycapitals

30. Use the cut command to print the 1st and 3rd columns of the /etc/passwd file for all students in this class.
$ cut -d: -f1,3 /etc/passwd

31. Count the number of people logged in and also trap the users in a file using the tee command.
$ who | tee users.txt | wc -l
comment
