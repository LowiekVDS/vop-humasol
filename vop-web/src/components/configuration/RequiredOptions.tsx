import { MenuItem, Select, TextField } from "@mui/material";
import { useEffect, useState } from "react";
import { FormattedMessage } from "react-intl";
import Button from "../Button";

export interface RequiredOptions {
  data?: RequiredOptionsData;
  onContinue: (data: RequiredOptionsData) => void;
}

export interface RequiredOptionsData {
  type?: "Receiver" | "Transmitter"; //'pump' | 'floatswitch' | 'waterlevelsensor'
  password?: string;
}

const nodeTypes = [
  { type: "Receiver", label: "Receiver" },
  { type: "Transmitter", label: "Transmitter" },
];

export default function RequiredOptions(props: RequiredOptions) {
  const [canContinue, setCanContinue] = useState<boolean>(false);
  const [data, setData] = useState<RequiredOptionsData>(props.data ?? {});

  const updateData = (field: keyof RequiredOptionsData, value: any) => {
    const newData = { ...data };
    newData[field] = value;
    setData(newData);
  };

  useEffect(() => {
    // Check if can continue
    setCanContinue(false);
    if (!data.type) {
      return;
    }

    if (!data.password || data?.password == "") {
      return;
    }

    setCanContinue(true);
  }, [data]);

  useEffect(() => {
  
    let propData: any = {};
    if (props.data) {
      propData = props.data as any;
    }

    if (propData && !propData?.type) {
      (propData as any).type = nodeTypes[0].type as any;
    }

    if (propData) {
      setData(propData as any);
    }
  }, [props.data]);


  return (
    <>
      <p className="mt-4 text-2xl font-bold">
        <FormattedMessage
          defaultMessage={"Required settings"}
          id={"Required settings"}
        />
      </p>

      <div className="grid w-1/2 gap-4 mt-4 items-left text-left mx-auto">
        <p className="font-bold text-gray-600">
          <FormattedMessage defaultMessage={"Node type"} id={"Node type"} />
        </p>
        <Select
          value={data.type ?? nodeTypes[0].type}
          onChange={(e) => updateData("type", e.target.value)}
        >
          {nodeTypes.map((nodeType) => (
            <MenuItem key={nodeType.type} value={nodeType.type}>
              {nodeType.label}
            </MenuItem>
          ))}
        </Select>
        <p className="font-bold text-gray-600">
          <FormattedMessage
            defaultMessage={"Network password"}
            id={"Network password"}
          />
        </p>
        <TextField
          value={data.password ?? ""}
          onChange={(e) => updateData("password", e.target.value)}
          type="password"
        />

        <Button
          onClick={() => props.onContinue(data)}
          disabled={!canContinue}
          className="mt-6"
        >
          <FormattedMessage defaultMessage={"Continue"} id={"Continue"} />
        </Button>
      </div>
    </>
  );
}
