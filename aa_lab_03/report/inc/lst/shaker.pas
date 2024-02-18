procedure sort_shaker(var arr: array of Integer);
begin
  m := Length(arr)
  i := 0
  while i < m do
  begin
    j := i + 1
    while j < m do
    begin
      if arr[j] < arr[j-1] then
      begin
        Swap(arr[j], arr[j-1])
      end
      j := j + 1
    end
    m := m - 1
    k := m - 1
    while k > i do
    begin
      if arr[k] < arr[k-1] then
      begin
        Swap(arr[k], arr[k-1])
      end
      k := k - 1
    end
    i := i + 1
  end
end
