module U = MaterialUi;
let s = ReactDOMRe.Style.make;

[%mui.withStyles
  "Styled"({
    paper: s(~display="flex", ~flex="1", ~alignItems="center", ~justifyContent="center", ~padding="10px", ()),
  })
];

let component = ReasonReact.statelessComponent("Login");

let make = (_children) => {
  ...component,
  render: (_self) =>
    <Styled render=(classes =>
      <U.Paper className=classes.paper>
        <div>
          {ReasonReact.string("Login")}
        </div>
      </U.Paper>
    )/>
};
