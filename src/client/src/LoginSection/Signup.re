module U = MaterialUi;
let s = ReactDOMRe.Style.make;

[%mui.withStyles
  "Styled"({
    form: s(~width="25%", ()),
    textFields: s(~display="flex", ~margin="10px 0", ~flexDirection="column", ()),
    button: s(~float="right", ()),
  })
];

type state = {
  username: string,
  password: string,
  forename: string,
  surname: string
};

type action =
  | UpdateUsername(string)
  | UpdatePassword(string)
  | UpdateForename(string)
  | UpdateSurname(string)
;

let updateUsername = (e, self) => {
  let e = e |> ReactEventRe.Form.target |> ReactDOMRe.domElementToObj;
  UpdateUsername(e##value) |> self.ReasonReact.send
}
let updatePassword = (e, self) => {
  let e = e |> ReactEventRe.Form.target |> ReactDOMRe.domElementToObj;
  UpdatePassword(e##value) |> self.ReasonReact.send
}
let updateForename = (e, self) => {
  let e = e |> ReactEventRe.Form.target |> ReactDOMRe.domElementToObj;
  UpdateForename(e##value) |> self.ReasonReact.send
}
let updateSurname = (e, self) => {
  let e = e |> ReactEventRe.Form.target |> ReactDOMRe.domElementToObj;
  UpdateSurname(e##value) |> self.ReasonReact.send
}

let component = ReasonReact.reducerComponent("Signup");

let make = (~signup, _children) => {
  ...component,
  initialState: () => { username: "", password: "", forename: "", surname: "" },
  reducer: (action, state) =>
    switch action {
    | UpdateUsername(username) => ReasonReact.Update({ ...state, username })
    | UpdatePassword(password) => ReasonReact.Update({ ...state, password })
    | UpdateForename(forename) => ReasonReact.Update({ ...state, forename })
    | UpdateSurname(surname) => ReasonReact.Update({ ...state, surname })
    },
  render: (self) =>
    <Styled render=(classes =>
      <form className=classes.form>
        <h2>{ReasonReact.string("Sign up")}</h2>
        <div className=classes.textFields>
          <U.TextField type_="text" fullWidth=true placeholder="Forename" label={ReasonReact.string("Forename")} value={`String(self.state.forename)} onChange={ self.handle(updateForename) } />
          <U.TextField type_="text" fullWidth=true placeholder="Surname" label={ReasonReact.string("Surname")} value={`String(self.state.surname)} onChange={ self.handle(updateSurname) } />

          <U.TextField type_="text" fullWidth=true placeholder="Username" label={ReasonReact.string("Username")} value={`String(self.state.username)} onChange={ self.handle(updateUsername) } />
          <U.TextField type_="password" fullWidth=true placeholder="Password" label={ReasonReact.string("Password")} value={`String(self.state.password)} onChange={ self.handle(updatePassword) } />
        </div>

        <U.Button className=classes.button variant=`Raised color=`Primary onClick={ (_e) => {
          User.create_signup_request(~forename=self.state.forename, ~surname=self.state.surname, ~username=self.state.username, ~password=self.state.password)
          |> signup
        } }>
          {ReasonReact.string("Sign up")}
        </U.Button>

      </form>
    )/>
};
