[%bs.raw {|require('./App.css')|}];

type state = {
  user: option(User.t)
};

type action =
  | LogIn(User.t)
;

let component = ReasonReact.reducerComponent("App");

let make = (_children) => {
  let login = ((username, password), self) => {
    User.login(username, password)
      |> Js.Promise.then_ (
        (user) => self.ReasonReact.send(LogIn(user)) |> Js.Promise.resolve
      )
      |> ignore
  };
  {
    ...component,
    initialState: () => { user: None },
    reducer: (action, _state) => {
      switch (action) {
      | LogIn(user) => ReasonReact.Update({ user: Some(user) })
      }
    },
    render: (self) =>
      <div className="App">
        <Header user=self.state.user/>

        <div className="app-body">
          {
            switch self.state.user {
            | Some(_user) => <Main />
            | None => <Login onSubmit={ self.handle(login) } />
            };
          }
        </div>
      </div>
  }
};
