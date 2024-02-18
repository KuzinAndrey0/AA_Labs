function smooth_sort(arr: array of Integer): array of Integer
  function leonardo(k: Integer): Integer
  begin
    if k < 2 then
      Result := 1
    else
      Result := leonardo(k - 1) + leonardo(k - 2) + 1
  end

  procedure heapify(start, ending: Integer);
  begin
    i := start
    j := 0
    k := 0
    while k < ending - start + 1 do
    begin
      if k and $AAAAAAAA <> 0 then
      begin
        j := j + i
        i := i shr 1
      end
      else
      begin
        i := i + j
        j := j shr 1
      end
      k := k + 1
    end
    while i > 0 do
    begin
      j := j shr 1
      k := i + j
      while k < ending do
      begin
        if arr[k] > arr[k - i] then
          break
        arr[k] := arr[k - i]
        arr[k - i] := arr[k]
        k := k + i
      end;
      i := j
    end
  end

begin
  n := Length(arr)
  p := n - 1
  q := p
  r := 0
  while p > 0 do
  begin
    if (r and $03) = 0 then
      heapify(r, q)
    if leonardo(r) = p then
      r := r + 1
    else
    begin
      r := r - 1
      q := q - leonardo(r)
      heapify(r, q)
      q := r - 1
      r := r + 1
    end
    arr[0] := arr[p]
    arr[p] := arr[0]
    p := p - 1
  end
  for i := 0 to n - 2 do
  begin
    j := i + 1
    while (j > 0) and (arr[j] < arr[j - 1]) do
    begin
      arr[j] := arr[j - 1]
      arr[j - 1] := arr[j]
      j := j - 1
    end
  end
  Result := arr
end
