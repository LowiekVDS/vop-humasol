import { ButtonUnstyled } from "@mui/base";
import React from "react";

export interface Button {
  color?: "standard" | "error";
  className?: string;
  disabled?: boolean;
  onClick?: () => void;
}

export default function Button(props: React.PropsWithChildren<Button>) {
  const color = props.color ? props.color : "standard";

  // Need to be statically evaluatable on build time
  const colors: Record<string, string> = {
    error: "bg-red-400 hover:bg-red-600",
    standard: "bg-amber-400 hover:bg-amber-600",
  };

  if (props.disabled) {
    return (
      <ButtonUnstyled
        disabled
        className={`bg-gray-400 rounded-lg h-12 uppercase font-bold ${props.className}`}
      >
        {props.children}
      </ButtonUnstyled>
    );
  } else {
    return (
      <ButtonUnstyled
        onClick={props.onClick}
        className={`transition-color transition-all hover:scale-105 ${colors[color]} rounded-lg h-12 uppercase font-bold ${props.className}`}
      >
        {props.children}
      </ButtonUnstyled>
    );
  }
}
