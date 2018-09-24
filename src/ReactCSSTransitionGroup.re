[@bs.module] external myJSReactClass: ReasonReact.reactClass = "react-addons-css-transition-group";

[@bs.deriving abstract]
type jsProps = {
  transitionName: string,
  transitionEnterTimeout: int,
  transitionLeaveTimeout: int,
};

let make = (~transitionName, ~transitionEnterTimeout, ~transitionLeaveTimeout, children) =>
  ReasonReact.wrapJsForReason(
    ~reactClass=myJSReactClass,
    ~props=jsProps(
        ~transitionName=transitionName,
        ~transitionEnterTimeout=transitionEnterTimeout,
        ~transitionLeaveTimeout=transitionLeaveTimeout
    ),
    children,
  )