using Plots
using Random

# # Define a new function that calls swap_and_record! with the appropriate arguments
# function swap_and_update!(arr, i, j, anim)
#   swap_and_record!(arr, i, j, anim, swap_condition=(x, y) -> x <= y)
# end

function update_animation!(arr, anim, idx=nothing)
  colors = fill(:blue, length(arr))
  if idx !== nothing && idx <= length(colors)
    colors[idx] = :red
  end

  p = bar(arr, ylims = (0, maximum(arr)), c = colors)
  frame(anim, p)
end

function animate_sorting(arr, sort_func, sort_func_args...)
  # Initialize the plot and animation
  p = bar(arr, ylims = (0, maximum(arr)))
  anim = Animation()
  # Define a function to compare and swap elements while updating the animation
  function swap_and_record!(arr, i, j, anim, update_only::Bool=false, changeWithValue::Bool=false, assendig::Bool=false, swap_condition::Function=(x, y) -> x > y)
    if changeWithValue
      arr[i] = j
    else
      if !assendig
        if update_only || swap_condition(arr[i], arr[j])
          if !update_only
            bufferMin = arr[j]
            bufferMax = arr[i]
            arr[i], arr[j] = bufferMin, bufferMax
          end
        end
      else
        if update_only || !swap_condition(arr[i], arr[j])
          if !update_only
            bufferMax = arr[j]
            bufferMin = arr[i]
            arr[i], arr[j] = bufferMax, bufferMin
          end
        end
      end
    end
    p = bar(arr, ylims = (0, maximum(arr))) # Update the plot
    frame(anim, p) # Record the current state of the array with the updated plot
  end
  # Sort the array using the provided sorting function and record the time taken
  sort_time = @elapsed sort_func(arr, swap_and_record!, anim, sort_func_args...)
  print("\nIt took $(sort_time)seconds to sort")

  # Add a final frame to the animation
  p = bar(arr, ylims = (0, maximum(arr)))
  frame(anim, p)

  # Save the animation as a gif
  gif(anim, "sorting_animation_$(string(sort_func)).gif", fps = 10)
end

# Define a function for bubble sort
function bubble_sort(arr, compare_and_swap!, anim)
  n = length(arr)
  for i in 1:n-1
    for j in 1:n-i
      compare_and_swap!(arr, j, j + 1, anim)
    end
  end
end

# Define a function for selection sort
function selection_sort(arr, compare_and_swap!, anim)
  # One by one move boundary of
  # unsorted subarray
  n = length(arr)
  for i in 1:n-1
    # Find the minimum element in
    # unsorted array
    min_idx = i
    for j in i+1:n
      if arr[j] < arr[min_idx]
        min_idx = j
      end
    
    end
    if min_idx!=1
      compare_and_swap!(arr, i, min_idx, anim)
    end
  end
end

function insertion_sort(arr, compare_and_swap!, anim)
  n = length(arr)

  # Traverse through 1 to len(arr)
  for i in 2:n
    key = arr[i]
    j = i - 1
    # Move elements of arr[0..i-1], that are
    # greater than key, to one position ahead
    # of their current position
    while j >= 1 && key < arr[j]
      compare_and_swap!(arr, j, j + 1, anim)
      j -= 1
    end
    arr[j + 1] = key
  end
end

function insertion_sort_recursive(arr, compare_and_swap!, anim, n=length(arr))
  # Base case: if the array has only one element, it is already sorted
  if n <= 1
    return
  end

  # Sort the first n-1 elements of the array recursively
  insertion_sort_recursive(arr, compare_and_swap!, anim, n - 1)

  # Insert the nth element into its correct position in the sorted subarray
  last = arr[n]
  j = n - 1

  # Shift elements to the right to make space for the nth element
  while j >= 1 && arr[j] > last
    compare_and_swap!(arr, j, j + 1, anim)
    j -= 1
  end

  # Place the nth element in its correct position
  arr[j + 1] = last
end


function partition(arr, low, high, compare_and_swap!, anim)
  pivot = arr[high]
  i = low - 1

  for j in low:high-1
    if arr[j] <= pivot
      i = i + 1
      compare_and_swap!(arr, i, j, anim)
    end
  end
  compare_and_swap!(arr, i+1, high, anim)

  return i + 1
end

function quick_sort(arr, compare_and_swap!, anim, low, high)
  if low < high
    pi = partition(arr, low, high, compare_and_swap!, anim)

    quick_sort(arr, compare_and_swap!, anim, low, pi - 1)
    quick_sort(arr, compare_and_swap!, anim, pi + 1, high)
  end
end

function bingo_sort(arr, swap_and_record!, anim)
  size = length(arr)
  # Finding the smallest element From the Array
  bingo = minimum(arr)
  # Finding the largest element from the Array
  largest = maximum(arr)
  next_bingo = largest
  next_pos = 1

  while bingo < next_bingo
    # Will keep the track of the element position to
    # shifted to their correct position
    start_pos = next_pos

    for i in start_pos:size
      if arr[i] == bingo
        swap_and_record!(arr, next_pos, i, anim)
        next_pos += 1
      #  Here we are finding the next Bingo Element
      #  for the next pass  
      elseif arr[i] < next_bingo
        next_bingo = arr[i]
      end
    end
    bingo = next_bingo
    next_bingo = largest
  end
end

function cocktail_sort(arr, swap_and_record!, anim)
  n = length(arr)
  swapped = true
  start = 1
  ending = n-1
  while swapped
    # Move from left to right
    for i in start:ending
      if arr[i] > arr[i + 1]
        swap_and_record!(arr, i, i+1, anim)
        swapped = true
      end
    end
    if !swapped
      break
    end
    ending -= 1
    # Move from right to left
    swapped = false
    for i in reverse(start: ending-1)
      if arr[i] > arr[i + 1]
        swap_and_record!(arr, i, i+1, anim)
        swapped = true
      end
    end
    start += 1
  end
end

function pigeonhole_sort(arr, swap_and_record!, anim)
  # size of range of values in the list
  # (ie, number of pigeonholes we need)
  my_min = minimum(arr)
  my_max = maximum(arr)
  size = my_max - my_min + 1

  # our list of pigeonholes
  holes = zeros(Int, size)

  # Populate the pigeonholes.
  for x in arr
    @assert isa(x, Int) "integers only please"
    holes[x - my_min + 1] += 1
  end

  # Put the elements back into the array in order.
  i = 1
  for (count, _) in enumerate(holes)
    while holes[count] > 0
      holes[count] -= 1
      swap_and_record!(arr, i, count + my_min, anim, false, true)
      i += 1
    end
  end
end

# It recursively sorts a bitonic sequence in ascending order,
# if dir = 1, and in descending order otherwise (means dir=0).
# The sequence to be sorted starts at index position low,
# the parameter cnt is the number of elements to be sorted.
function bitonic_merge(arr, low, cnt, dire, swap_and_record!, anim)
  if cnt > 1
    k = cnt//2
  end
  for i in low:low+k
    swap_and_record!(arr, i, i+k+1, anim, false, false, true)
  end
  bitonic_merge(arr, low, k, dire, swap_and_record!, anim)
  bitonic_merge(arr, low+k, k, dire, swap_and_record!, anim)
end

# This function first produces a bitonic sequence by recursively
# sorting its two halves in opposite sorting orders, and then
# calls bitonicMerge to make them in the same order
function bitonic_sort(arr, low, cnt, dire, swap_and_record!, anim)
  if cnt > 1
    k = cnt//2
    bitonic_sort(arr, low, k, 1, swap_and_record!, anim)
    bitonic_sort(arr, low+k, k, 0, swap_and_record!, anim)
    bitonic_merge(arr, low, cnt, dire, swap_and_record!, anim)
  end
end

# Caller of bitonicSort for sorting the entire array of length N
# in ASCENDING order
function run_bitonic_sort(arr, swap_and_record!, anim)
  N = length(arr)
  up = 1
  bitonic_sort(arr, 0, N, up, swap_and_record!, anim)
end

function gpu_sort_for_cpu(arr, swap_and_record!, anim)
  step = 1
  while 2^step <= length(arr)
    for i in 1:length(arr)//step
      recursiveSorting(arr, i%2==1, 2^step,i*step,swap_and_record!,anim)
    end
    step+=1
  end
end

function recursiveSorting(arr, dir,width,start,swap_and_record!,anim)
  if(width >= 2)
    for i in start:start+div(width,2)
      swap_and_record!(arr,Int(i),i+div(width,2),anim,false, false, dir)
    end
    recursiveSorting(arr, dir, div(width,2),start,swap_and_record!,anim)
    recursiveSorting(arr, dir,div(width,2),start+div(width,2),swap_and_record!,anim)
  end
end

# Initialize the random number generator for reproducibility
Random.seed!(42)

# Generate an array of random integers
arr = rand(1:50, 32)

# # Call the animate_sorting function with the array and the quick_sort function
# print("Starting to generate quick_sort animation...")
# animate_sorting(copy(arr), quick_sort, 1, length(arr))

# # Call the animate_sorting function with the array and the selection_sort function
# print("Starting to generate selection_sort animation...")
# animate_sorting(copy(arr), selection_sort)

# # Call the animate_sorting function with the array and the insertion_sort function
# print("Starting to generate insertion_sort animation...")
# animate_sorting(copy(arr), insertion_sort)

# # Call the animate_sorting function with the array and the recursive version of insertion_sort function
# print("Starting to generate insertion_sort_recursive animation...")
# animate_sorting(copy(arr), insertion_sort_recursive)

# # Call the animate_sorting function with the array and the bingo_sort function
# println("Starting to generate bingo_sort animation...")
# animate_sorting(copy(arr), bingo_sort)

# # Call the animate_sorting function with the array and the bubble_sort function
# print("Starting to generate bubble_sort animation...")
# animate_sorting(copy(arr), bubble_sort)

# # Call the animate_sorting function with the array and the bubble_sort function
# print("Starting to generate cocktail_sort animation...")
# animate_sorting(copy(arr), cocktail_sort)

# # Call the animate_sorting function with the array and the pigeonhole_sort function
# print("Starting to generate pigeonhole_sort animation...")
# animate_sorting(copy(arr), pigeonhole_sort)