
type t = {
  id: int;
  username: string;
  forename: string;
  surname: string;
};;

let create ~id ~username () = {
  id;
  username;
  forename = username;
  surname = username;
};;

let create_from_json json =
  let open Json.Decode in
  let u = {
    id = json |> field "user_id" int;
    username = json |> field "username" string;
    forename = json |> field "forename" string;
    surname = json |> field "surname" string;
  } in
  Js.log u; u
;;

let login username password =
  let open Js.Promise in
  let req_init = Api.make_request_init [
    ("username", Js.Json.string username);
    ("password", Js.Json.string password)
  ] in
  Fetch.fetchWithInit "/authenticate/login" req_init
  |> then_ Fetch.Response.json
  |> then_ (
    fun result -> create_from_json result |> resolve
  )

