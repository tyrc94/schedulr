let make_request_init lst =
  let payload = Js.Dict.fromList lst in
  let body = Js.Json.object_ payload
    |> Js.Json.stringify
    |> Fetch.BodyInit.make
  in
  let headers = Js.Dict.fromList [
      ("Content-Type", "application/json")
    ] |> Fetch.HeadersInit.makeWithDict
  in
  Fetch.RequestInit.make ~method_:Post ~body ~headers ()
;;
