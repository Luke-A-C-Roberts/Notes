defmodule Msg do
  def send_on_heap,  do: send(:on_heap)
  def send_off_heap, do: send(:off_heap)

  defp send(how) do
    # Spawn a function that loops for a while
    p2 = spawn(fn -> receiver(how) end)
    # spawn a sending process
    p1 = spawn(fn -> sender(p2) end)
    p1
  end

  defp sender(p2) do
    # Send a message that ends up on the heap
    m = loop(0)
    send(p2, self())
    receive do
      :ready -> :ok
    end
    send(p2, m)
    :ok
  end

  defp receiver(how) do
    Process.flag(:message_queue_data, how)
    send(self(), :ready)
    receive do
      :x -> :ok
    end
  end

  defp loop(0), do: [:done]
  defp loop(n), do: [loop(n - 1)]
end


