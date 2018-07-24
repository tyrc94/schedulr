module U = MaterialUi;
let s = ReactDOMRe.Style.make;

[%mui.withStyles
  "Styled"({
    root: s(~flexGrow="1", ()),
    flex: s(~flexGrow="1", ()),
    menuButton: s(
      ~marginLeft="-12",
      ~marginRight="20",
      ()
    )
  })
];

let component = ReasonReact.statelessComponent("Header");

let make = (_children) => {
  ...component,
  render: (_self) =>
    <Styled render=(classes =>
      <div className="Header">
        <U.AppBar position=`Static>
          <U.Toolbar>
            <U.IconButton className=classes.menuButton color=`Inherit>
              <U.Icon>{ReasonReact.string("menu")}</U.Icon>
            </U.IconButton>
            <U.Typography variant=`Title color=`Inherit className=classes.flex>
              {ReasonReact.string("Schedulr")}
            </U.Typography>
            <U.Button color=`Inherit>{ReasonReact.string("Login")}</U.Button>
          </U.Toolbar>
        </U.AppBar>
      </div>
    )/>
};
