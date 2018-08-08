[%bs.raw {|require('./App.css')|}];

type state = {
  user: option(User.t)
};

type action =
  | LogIn(User.t)
;

let login = ((username, password), self) => {
  User.login(username, password)
    |> Js.Promise.then_ (
      (user) => self.ReasonReact.send(LogIn(user)) |> Js.Promise.resolve
    )
    |> ignore
};


let component = ReasonReact.reducerComponent("App");

let make = (_children) => {
  ...component,
  initialState: () => { user: None },
  reducer: (action, _state) => {
    switch (action) {
    | LogIn(user) => ReasonReact.Update({ user: Some(user) })
    }
  },
  render: (self) => {
    let signup = (signupRequest) => {
      User.signup(signupRequest)
        |> Js.Promise.then_ (
          (result) => Js.log(result) |> Js.Promise.resolve
        )
    };

    (
      <div className="App">
        <Header user=self.state.user/>

        <div className="app-body">
          {
            switch self.state.user {
            | Some(_user) => <Main />
            | None => <LoginSection login={ self.handle(login) } signup />
            };
          }
        </div>
      </div>
    )
  }
};
