[%bs.raw {|require('./App.css')|}];

type state = {
  appState: option(AppState.t)
};

type action =
  | LogIn(AppState.t)
;

let component = ReasonReact.reducerComponent("App");

let make = (_children) => {
  ...component,
  initialState: () => { appState: None },
  reducer: (action, state) => {
    switch (action) {
    | LogIn(appState) => ReasonReact.Update({ appState: Some(appState) })
    }
  },
  render: (self) =>
    <div className="App">
      <Header appState=self.state.appState/>

      <div className="app-body">
        {
          switch self.state.appState {
          | Some(_appState) => <Main />
          | None => <Login onSubmit={ (username, password) => { LogIn(AppState.create(~username, ~password, ())) |> self.send } } />
          };
        }
      </div>
    </div>
};
