import { MenuItem, Select, TextField } from "@mui/material";
import { useEffect, useState } from "react";
import { FormattedMessage } from "react-intl";
import Button from "../Button";
import NumberInput from "semantic-ui-react-numberinput";

console.log(NumberInput);

export interface AdvancedOptions {
  data?: AdvancedOptionsData;
  onContinue: (data: AdvancedOptionsData) => void;
}

export interface AdvancedOptionsData {
  LoRaSpreadFactor?: number;
  bandwidth?: number;
  txPower?: number;
}

const supportedBandwidth = [
  7.8, 10.4, 15.6, 20.8, 31.2, 41.7, 62.5, 125, 250, 500,
];

const supportedSpread = [7, 8, 9, 10, 11, 12];

const supportedPower = [
  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
];

export default function AdvancedOptions(props: AdvancedOptions) {
  const [canContinue, setCanContinue] = useState<boolean>(true);
  const [data, setData] = useState<AdvancedOptionsData>(props.data ?? {});

  const updateData = (field: keyof AdvancedOptionsData, value: any) => {
    const newData = { ...data };
    newData[field] = value;
    setData(newData);
  };

  useEffect(() => {
    let propData: AdvancedOptionsData = {
      LoRaSpreadFactor: 7,
      txPower: 15,
      bandwidth: 250,
    };
    if (props.data) {
      propData = props.data as any;
    }

    if (propData) {
      setData(propData as any);
    }
  }, [props.data]);

  return (
    <>
      <p className="mt-4 text-2xl font-bold">
        <FormattedMessage
          defaultMessage={"Advanced settings"}
          id={"Advanced settings"}
        />
      </p>

      <div className="grid w-1/2 gap-4 mt-4 items-left text-left mx-auto">
        <p className="font-bold text-gray-600">
          <FormattedMessage
            defaultMessage={"Spreading factor"}
            id={"Spreading factor"}
          />
        </p>

        <Select
          value={data.LoRaSpreadFactor ?? supportedSpread[0]}
          onChange={(e) => updateData("LoRaSpreadFactor", e.target.value)}
        >
          {supportedSpread.map((bw) => (
            <MenuItem key={bw} value={bw}>
              {bw}
            </MenuItem>
          ))}
        </Select>

        <p className="font-bold text-gray-600">
          <FormattedMessage
            defaultMessage={"TX Power (dBm)"}
            id={"TX Power (dBm)"}
          />
        </p>

        <Select
          value={data.txPower ?? supportedPower[0]}
          onChange={(e) => updateData("txPower", e.target.value)}
        >
          {supportedPower.map((bw) => (
            <MenuItem key={bw} value={bw}>
              {bw}
            </MenuItem>
          ))}
        </Select>

        <p className="font-bold text-gray-600">
          <FormattedMessage defaultMessage={"Bandwidth"} id={"Bandwidth"} />
        </p>

        <Select
          value={data.bandwidth ?? supportedBandwidth[0]}
          onChange={(e) => updateData("bandwidth", e.target.value)}
        >
          {supportedBandwidth.map((bw) => (
            <MenuItem key={bw} value={bw}>
              {bw} kHz
            </MenuItem>
          ))}
        </Select>

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
