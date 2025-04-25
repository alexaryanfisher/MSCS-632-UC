(* OCaml Statistics Calculator *)

(* Calculate the mean of the numbers*)
let mean numbers =
  let sum = List.fold_left (+.) 0.0 numbers in
  sum /. float_of_int (List.length numbers)

(* Calculate the median of the numbers *)
let median numbers =
  let sorted = List.sort compare numbers in
  let len = List.length sorted in
  if len mod 2 = 0 then
    let mid1 = List.nth sorted (len / 2 - 1) in
    let mid2 = List.nth sorted (len / 2) in
    (mid1 +. mid2) /. 2.0
  else
    List.nth sorted (len / 2)

(* Calculate the mode of the numbers *)
let mode numbers =
  let count_map = List.fold_left (fun acc x ->
    let count = try List.assoc x acc with Not_found -> 0 in
    (x, count + 1) :: List.remove_assoc x acc
  ) [] numbers in
  let max_count = List.fold_left (fun acc (_, count) ->
    max acc count
  ) 0 count_map in
  List.filter (fun (_, count) -> count = max_count) count_map

 (* Main Function, show the original numbers and calculated mean, median, and mode. *)
 let () =
  let numbers = [1.0; 2.0; 2.0; 2.0; 3.0; 5.0; 5.0; 5.0; 5.0; 7.0] in
  let mean_value = mean numbers in
  let median_value = median numbers in
  let mode_value = mode numbers in

(* Print results*)
  Printf.printf "Numbers: %s\n"
    (String.concat "; " (List.map string_of_float numbers));
  
  if Float.is_nan mean_value then
    Printf.printf "Mean: No numbers provided. Empty list.\n"
  else
    Printf.printf "Mean: %f\n" mean_value;
  if Float.is_nan median_value then
    Printf.printf "Median: No numbers provided. Empty list.\n"
  else
    Printf.printf "Median: %.2f\n" median_value;
  
  if List.length mode_value = 0 then
    Printf.printf "Mode: No numbers provided. Empty list.\n"
  else
    Printf.printf "Mode: %s\n"
      (String.concat ", " (List.map (fun (x, _) -> string_of_float x) mode_value));
